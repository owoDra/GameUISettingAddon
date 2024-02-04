// Copyright (C) 2024 owoDra

#include "SettingUIListEntry.h"

#include "Resolver/SettingUITypeResolver.h"

#include "CommonInputSubsystem.h"
#include "CommonInputTypeEnum.h"
#include "CommonTextBlock.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUIListEntry)


USettingUIListEntry::USettingUIListEntry(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void USettingUIListEntry::SetSetting(USettingUITypeResolver* InSetting)
{
	Setting = InSetting;
	check(Setting.IsValid());

	Setting->OnPropertyValueChange.AddUObject(this, &ThisClass::HandleSettingValueChanged);
	Setting->OnEditStateChange.AddUObject(this, &ThisClass::HandleEditableStateChanged);

	if (Text_SettingName)
	{
		Text_SettingName->SetText(Setting->GetDisplayName());
	}

	HandleSettingValueChanged(Setting.Get());
	HandleEditableStateChanged(Setting.Get(), Setting->GetEditableState());
}

void USettingUIListEntry::NativeOnEntryReleased()
{
	StopAllAnimations();

	if (Background)
	{
		Background->StopAllAnimations();
	}

	if (ensure(Setting.IsValid()))
	{
		Setting->OnPropertyValueChange.RemoveAll(this);
		Setting->OnEditStateChange.RemoveAll(this);
	}

	Setting = nullptr;
}

void USettingUIListEntry::HandleSettingValueChanged(USettingUITypeResolver* InSetting)
{
	OnSettingValueChanged(InSetting);
}

void USettingUIListEntry::HandleEditableStateChanged(USettingUITypeResolver* InSetting, const FSettingUIEditableState& InEditableState)
{
	OnEditableStateChanged(InSetting, InEditableState);
}


FReply USettingUIListEntry::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	const auto* InputSubsystem{ GetInputSubsystem() };

	if (InputSubsystem && InputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
	{
		if (auto* PrimaryFocus{ GetPrimaryGamepadFocusWidget() })
		{
			auto WidgetToFocus{ PrimaryFocus->GetCachedWidget() };

			if (WidgetToFocus.IsValid())
			{
				return FReply::Handled().SetUserFocus(WidgetToFocus.ToSharedRef(), InFocusEvent.GetCause());
			}
		}
	}

	return FReply::Unhandled();
}
