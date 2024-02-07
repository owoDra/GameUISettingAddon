// Copyright (C) 2024 owoDra

#include "SettingUITypeResolver.h"

#include "EditCondition/SettingUIEditCondition.h"
#include "SettingUISubsystem.h"

#include "GSCGameUserSettings.h"
#include "GSCSubsystem.h"

#include "ICommonUIModule.h"
#include "CommonUISettings.h"

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

	OnInitialized();
}

void USettingUITypeResolver::OnInitialized()
{
	UpdateEditableState();
	NotifyPropertyOptionChange();	// It must always be executed before NotifyPropertyValueChange(). 
	NotifyPropertyValueChange();	// This is because the widget will not reflect the change properly.
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
	NotifyPropertyOptionChange();	// It must always be executed before NotifyPropertyValueChange(). 
	NotifyPropertyValueChange();	// This is because the widget will not reflect the change properly.
}


// Setting Data

UObject* USettingUITypeResolver::GetSource() const
{
	if (auto* GSCGUS{ UGSCGameUserSettings::GetGSCGameUserSettings() })
	{
		if (auto SourceClass{ Data.Accessor.Source })
		{
			if (auto* Subsystem{ GSCGUS->GetSubsystemBase(SourceClass) })
			{
				return Subsystem;
			}
		}
		else
		{
			return GSCGUS;
		}
	}

	UE_LOG(LogGameCore_Settings, Error, TEXT("Failed to get source object for setting(%s)"), *DevName.ToString());

	return nullptr;
}

void USettingUITypeResolver::NotifyPropertyValueChange(bool bBroadcastDependancies)
{
	OnPropertyValueChange.Broadcast(this);

	if (bBroadcastDependancies && OwnerSubsystem.IsValid())
	{
		OwnerSubsystem->NotifySettingsUpdate(Data.DependentSettings);
	}
}

void USettingUITypeResolver::NotifyPropertyOptionChange()
{
	OnPropertyOptionChange.Broadcast(this);
}


// Editable State

void USettingUITypeResolver::UpdateEditableState()
{
	EditableState = EditCondition ? EditCondition->ComputeEditableState() : FSettingUIEditableState::Editable;

	NativeEditCondition(EditableState);

	if (Data.RequestTraitTags.IsValid())
	{
		const auto bHasAllTrait{ ICommonUIModule::Get().GetSettings().GetPlatformTraits().HasAll(Data.RequestTraitTags) };
		EditableState = bHasAllTrait ? EditableState : FSettingUIEditableState::Collapsed;
	}

	OnEditStateChange.Broadcast(this, EditableState);
}

void USettingUITypeResolver::NativeEditCondition(FSettingUIEditableState& InOutEditableState)
{
}
