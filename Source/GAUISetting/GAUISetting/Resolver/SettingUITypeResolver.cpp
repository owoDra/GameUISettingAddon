// Copyright (C) 2024 owoDra

#include "SettingUITypeResolver.h"

#include "EditCondition/SettingUIEditCondition.h"
#include "SettingUISubsystem.h"

#include "GSCGameUserSettings.h"
#include "GSCSubsystem.h"

#include "GSCoreLogs.h"

#include "ICommonUIModule.h"
#include "CommonUISettings.h"
#include "PropertyPathHelpers.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUITypeResolver)


USettingUITypeResolver::USettingUITypeResolver(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


#if WITH_EDITOR

UFunction* USettingUITypeResolver::GetGetterTemplate(const UClass* ResolverClass)
{
	if (ResolverClass)
	{
		static const FName NAME_GetterTemplate{ TEXTVIEW("GetterTemplate") };

		return ResolverClass->FindFunctionByName(NAME_GetterTemplate);
	}

	return nullptr;
}

UFunction* USettingUITypeResolver::GetSetterTemplate(const UClass* ResolverClass)
{
	if (ResolverClass)
	{
		static const FName NAME_SetterTemplate{ TEXTVIEW("SetterTemplate") };

		return ResolverClass->FindFunctionByName(NAME_SetterTemplate);
	}

	return nullptr;
}

UFunction* USettingUITypeResolver::GetOptionGetterTemplate(const UClass* ResolverClass)
{
	if (ResolverClass)
	{
		static const FName NAME_OptionGetterTemplate{ TEXTVIEW("OptionGetterTemplate") };

		return ResolverClass->FindFunctionByName(NAME_OptionGetterTemplate);
	}

	return nullptr;
}

#endif


// Initialization

void USettingUITypeResolver::InitializeResolver(USettingUISubsystem* Subsystem, const FName& InDevName, const FSettingUIOption& OptionData)
{
	OwnerSubsystem = Subsystem;
	DevName = InDevName;
	Data = OptionData;

	if (Data.EditCondition)
	{
		EditCondition = NewObject<USettingUIEditCondition>(this, Data.EditCondition);
		EditCondition->InitializeEditCondition(this);
	}

	UpdateEditableState();
	NotifyPropertyValueChange();
}

void USettingUITypeResolver::ReleaseResolver()
{
	if (EditCondition)
	{
		EditCondition->DeinitializeEditCondition();
	}

	OwnerSubsystem.Reset();
}

void USettingUITypeResolver::ReEvaluateOption()
{
	UpdateEditableState();
	NotifyPropertyValueChange();
}


// Setting Data

FString USettingUITypeResolver::GetPropertyValueAsString() const
{
	if (auto* Subsystem{ UGSCGameUserSettings::GetSettingSubsystemBase(Data.Accessor.Source) })
	{
		FString OutValue;

		if (PropertyPathHelpers::GetPropertyValueAsString(Subsystem, Data.Accessor.GetterName.ToString(), OutValue))
		{
			return OutValue;
		}
		else
		{
			UE_LOG(LogGameCore_Settings, Error, TEXT("Failed to get value from [%s::%s]"), *GetNameSafe(Subsystem), *Data.Accessor.GetterName.ToString());
		}
	}
	else
	{
		UE_LOG(LogGameCore_Settings, Error, TEXT("Failed to get value because invalid setting subsystem"));
	}

	return FString();
}

bool USettingUITypeResolver::SetPropertyValueFromString(const FString& StringValue)
{
	if (auto* Subsystem{ UGSCGameUserSettings::GetSettingSubsystemBase(Data.Accessor.Source) })
	{
		if (PropertyPathHelpers::SetPropertyValueFromString(Subsystem, Data.Accessor.SetterName.ToString(), StringValue))
		{
			NotifyPropertyValueChange(true);
			return true;
		}
		else
		{
			UE_LOG(LogGameCore_Settings, Error, TEXT("Failed to set value from [%s::%s]"), *GetNameSafe(Subsystem), *Data.Accessor.SetterName.ToString());
		}
	}
	else
	{
		UE_LOG(LogGameCore_Settings, Error, TEXT("Failed to set value because invalid setting subsystem"));
	}

	return false;
}

void USettingUITypeResolver::NotifyPropertyValueChange(bool bBroadcastDependancies)
{
	OnPropertyValueChange.Broadcast(this);

	if (bBroadcastDependancies)
	{
		OwnerSubsystem->NotifySettingsUpdate(Data.DependentSettings);
	}
}


// Editable State

void USettingUITypeResolver::UpdateEditableState()
{
	EditableState = EditCondition ? EditCondition->ComputeEditableState() : FSettingUIEditableState::Editable;

	if (Data.RequestTraitTags.IsValid())
	{
		const auto bHasAllTrait{ ICommonUIModule::Get().GetSettings().GetPlatformTraits().HasAll(Data.RequestTraitTags) };
		EditableState = bHasAllTrait ? EditableState : FSettingUIEditableState::Collapsed;
	}

	OnEditStateChange.Broadcast(this, EditableState);
}
