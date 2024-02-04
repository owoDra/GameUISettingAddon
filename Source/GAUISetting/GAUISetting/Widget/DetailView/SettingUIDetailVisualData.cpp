// Copyright (C) 2024 owoDra

#include "SettingUIDetailVisualData.h"

#include "Resolver/SettingUITypeResolver.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUIDetailVisualData)

///////////////////////////////////////////////////////////////////////////

USettingUIDetailVisualData::USettingUIDetailVisualData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


TArray<TSoftClassPtr<USettingUIDetailExtension>> USettingUIDetailVisualData::GatherDetailExtensions(const USettingUITypeResolver* InSetting) const
{
	TArray<TSoftClassPtr<USettingUIDetailExtension>> Extensions;

	// Find extensions by setting name

	if (auto* ExtensionsWithName{ ExtensionsForName.Find(InSetting->GetDevName()) })
	{
		Extensions.Append(ExtensionsWithName->Extensions);

		if (!ExtensionsWithName->bIncludeClassDefaultExtensions)
		{
			return Extensions;
		}
	}

	// Find extensions for it using the super chain of the setting so that we get any
	// class based extensions for this setting.

	for (auto* Class{ InSetting->GetClass() }; Class; Class = Class->GetSuperClass())
	{
		if (auto SettingClass{ TSubclassOf<USettingUITypeResolver>(Class) })
		{
			if (auto* ExtensionForClass{ ExtensionsForClasses.Find(SettingClass) })
			{
				Extensions.Append(ExtensionForClass->Extensions);
			}
		}
	}

	return Extensions;
}
