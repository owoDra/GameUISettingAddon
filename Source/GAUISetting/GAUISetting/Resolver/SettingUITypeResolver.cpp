// Copyright (C) 2024 owoDra

#include "SettingUITypeResolver.h"

#include "GSCGameUserSettings.h"
#include "GSCSubsystem.h"

#include "GSCoreLogs.h"

#include "PropertyPathHelpers.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUITypeResolver)


USettingUITypeResolver::USettingUITypeResolver(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


#if WITH_EDITOR

UFunction* USettingUITypeResolver::GetGetterTemplate(const UClass* ResolverClass)
{
	check(ResolverClass);

	static const FName NAME_GetterTemplate{ TEXTVIEW("GetterTemplate") };

	return ResolverClass->FindFunctionByName(NAME_GetterTemplate);
}

UFunction* USettingUITypeResolver::GetSetterTemplate(const UClass* ResolverClass)
{
	check(ResolverClass);

	static const FName NAME_SetterTemplate{ TEXTVIEW("SetterTemplate") };

	return ResolverClass->FindFunctionByName(NAME_SetterTemplate);
}

UFunction* USettingUITypeResolver::GetOptionGetterTemplate(const UClass* ResolverClass)
{
	check(ResolverClass);

	static const FName NAME_OptionGetterTemplate{ TEXTVIEW("OptionGetterTemplate") };

	return ResolverClass->FindFunctionByName(NAME_OptionGetterTemplate);
}

#endif


void USettingUITypeResolver::InitializeResolver(const FSettingUIOption& OptionData)
{
	DisplayName = OptionData.Name;
	Description = OptionData.Description;
	GetterName = OptionData.Accessor.GetterName;
	SetterName = OptionData.Accessor.SetterName;
	OptionGetterName = OptionData.Accessor.OptionGetterName;

	auto* SubsystemClass
	{
		OptionData.Accessor.Source.IsValid() ? OptionData.Accessor.Source.Get() : OptionData.Accessor.Source.LoadSynchronous()
	};

	auto* FoundSubsystem{ UGSCGameUserSettings::GetSettingSubsystemBase(SubsystemClass) };
	if (ensure(FoundSubsystem))
	{
		SourceSubsystem = FoundSubsystem;
	}
}


FString USettingUITypeResolver::GetPropertyValueAsString() const
{
	if (SourceSubsystem.IsValid())
	{
		FString OutValue;

		if (PropertyPathHelpers::GetPropertyValueAsString(SourceSubsystem.Get(), GetterName.ToString(), OutValue))
		{
			return OutValue;
		}
		else
		{
			UE_LOG(LogGameCore_Settings, Error, TEXT("Failed to get value from [%s::%s]"), *GetNameSafe(SourceSubsystem.Get()), *GetterName.ToString());
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
	if (SourceSubsystem.IsValid())
	{
		if (PropertyPathHelpers::SetPropertyValueFromString(SourceSubsystem.Get(), SetterName.ToString(), StringValue))
		{
			return true;
		}
		else
		{
			UE_LOG(LogGameCore_Settings, Error, TEXT("Failed to set value from [%s::%s]"), *GetNameSafe(SourceSubsystem.Get()), *SetterName.ToString());
		}
	}
	else
	{
		UE_LOG(LogGameCore_Settings, Error, TEXT("Failed to set value because invalid setting subsystem"));
	}

	return false;
}
