// Copyright (C) 2023 owoDra

#include "SettingUIListEntry_Switch.h"

#include "Resolver/SettingUITypeResolver_Switch.h"

#include "CommonRotator.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUIListEntry_Switch)


USettingUIListEntry_Switch::USettingUIListEntry_Switch(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void USettingUIListEntry_Switch::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Rotator_SettingValue->OnRotatedEvent.AddUObject(this, &ThisClass::HandleRotatorChangedValue);
	Button_Decrease->OnClicked().AddUObject(this, &ThisClass::HandleOptionDecrease);
	Button_Increase->OnClicked().AddUObject(this, &ThisClass::HandleOptionIncrease);
}


void USettingUIListEntry_Switch::HandleSettingValueChanged(USettingUITypeResolver* InSetting)
{
	auto* SwitchResolver{ Cast<USettingUITypeResolver_Switch>(InSetting) };
	if (ensure(SwitchResolver))
	{
		Rotator_SettingValue->SetSelectedItem(SwitchResolver->GetSettingValue());
	}

	Super::HandleSettingValueChanged(InSetting);
}

void USettingUIListEntry_Switch::HandleSettingOptionChanged(USettingUITypeResolver* InSetting)
{
	if (ensure(InSetting))
	{
		auto Options{ InSetting->GetOptionDisplayTexts() };

		if (ensure(!Options.IsEmpty()))
		{
			Rotator_SettingValue->PopulateTextLabels(Options);
		}
	}

	Super::HandleSettingOptionChanged(InSetting);
}


void USettingUIListEntry_Switch::HandleOptionDecrease()
{
	Rotator_SettingValue->ShiftTextLeft();
	SetSettingValue(Rotator_SettingValue->GetSelectedIndex());
}

void USettingUIListEntry_Switch::HandleOptionIncrease()
{
	Rotator_SettingValue->ShiftTextRight();
	SetSettingValue(Rotator_SettingValue->GetSelectedIndex());
}

void USettingUIListEntry_Switch::HandleRotatorChangedValue(int32 Value, bool bUserInitiated)
{
	if (bUserInitiated)
	{
		SetSettingValue(Value);
	}
}


void USettingUIListEntry_Switch::SetSettingValue(int32 NewValue)
{
	auto* SwitchResolver{ GetResolver<USettingUITypeResolver_Switch>() };
	if (ensure(SwitchResolver))
	{
		SwitchResolver->SetSettingValue(NewValue);
	}
}
