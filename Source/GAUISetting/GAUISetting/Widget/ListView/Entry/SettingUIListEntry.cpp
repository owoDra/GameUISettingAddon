// Copyright (C) 2024 owoDra

#include "SettingUIListEntry.h"

#include "Resolver/SettingUITypeResolver.h"
#include "Widget/ListView/SettingUIListView.h"

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
	check(Setting);

	Setting->OnPropertyValueChange.AddUObject(this, &ThisClass::HandleSettingValueChanged);
	Setting->OnPropertyOptionChange.AddUObject(this, &ThisClass::HandleSettingOptionChanged);
	Setting->OnEditStateChange.AddUObject(this, &ThisClass::HandleEditableStateChanged);

	if (Text_SettingName)
	{
		Text_SettingName->SetText(Setting->GetDisplayName());
	}

	HandleSettingOptionChanged(Setting);
	HandleSettingValueChanged(Setting);
	HandleEditableStateChanged(Setting, Setting->GetEditableState());
}

void USettingUIListEntry::NativeOnEntryReleased()
{
	StopAllAnimations();

	if (Background)
	{
		Background->StopAllAnimations();
	}

	if (ensure(Setting))
	{
		Setting->OnPropertyValueChange.RemoveAll(this);
		Setting->OnPropertyOptionChange.RemoveAll(this);
		Setting->OnEditStateChange.RemoveAll(this);
	}

	Setting = nullptr;
}


void USettingUIListEntry::HandleSettingValueChanged(USettingUITypeResolver* InSetting)
{
	OnSettingValueChanged(InSetting);
}

void USettingUIListEntry::HandleSettingOptionChanged(USettingUITypeResolver* InSetting)
{
	OnSettingOptionChanged(InSetting);
}

void USettingUIListEntry::HandleEditableStateChanged(USettingUITypeResolver* InSetting, const FSettingUIEditableState& InEditableState)
{
	SetIsEnabled(InEditableState.bEnabled);
	
	if (Background)
	{
		Background->SetVisibility(InEditableState.bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}

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
