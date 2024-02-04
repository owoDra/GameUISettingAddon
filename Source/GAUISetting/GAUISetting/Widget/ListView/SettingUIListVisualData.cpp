// Copyright (C) 2024 owoDra

#include "SettingUIListVisualData.h"

#include "Resolver/SettingUITypeResolver.h"
#include "SettingUIListEntry.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUIListVisualData)

/////////////////////////////////////////////////////////////////////////

USettingUIListVisualData::USettingUIListVisualData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


TSubclassOf<USettingUIListEntry> USettingUIListVisualData::GetEntryForSetting(USettingUITypeResolver* InSetting) const
{
	if (InSetting)
	{
		// Check if there's a custom logic for finding this setting's visual element

		if (auto CustomEntry{ GetCustomEntryForSetting(InSetting) })
		{
			return CustomEntry;
		}

		// Check if there's a specific entry widget for a setting by name.

		if (auto EntryWidgetClass_ByName{ EntryWidgetForName.FindRef(InSetting->GetDevName()) })
		{
			return EntryWidgetClass_ByName;
		}

		// Finally check to see if there's an entry for this setting following the classes we have entries for.

		for (auto* Class{ InSetting->GetClass() }; Class; Class = Class->GetSuperClass())
		{
			if (auto SettingClass{ TSubclassOf<USettingUITypeResolver>(Class) })
			{
				if (auto EntryWidgetClass_ByClass{ EntryWidgetForClass.FindRef(SettingClass) })
				{
					return EntryWidgetClass_ByClass;
				}
			}
		}
	}

	return nullptr;
}

TSubclassOf<USettingUIListEntry> USettingUIListVisualData::GetCustomEntryForSetting(USettingUITypeResolver* InSetting) const
{
	return TSubclassOf<USettingUIListEntry>();
}
