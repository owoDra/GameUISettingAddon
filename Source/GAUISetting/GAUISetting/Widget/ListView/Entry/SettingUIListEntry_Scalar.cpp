// Copyright (C) 2023 owoDra

#include "SettingUIListEntry_Scalar.h"

#include "Resolver/SettingUITypeResolver_Scalar.h"

#include "AnalogSlider.h"
#include "Components/SpinBox.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUIListEntry_Scalar)


USettingUIListEntry_Scalar::USettingUIListEntry_Scalar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void USettingUIListEntry_Scalar::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Slider_SettingValue->OnValueChanged.AddDynamic(this, &ThisClass::HandleSliderValueChange);
	Slider_SettingValue->OnControllerCaptureEnd.AddDynamic(this, &ThisClass::HandleSliderValueCommit);
	Slider_SettingValue->OnMouseCaptureEnd.AddDynamic(this, &ThisClass::HandleSliderValueCommit);
	Spin_SettingValue->OnValueCommitted.AddDynamic(this, &ThisClass::HandleSpinValueCommit);
}


void USettingUIListEntry_Scalar::HandleSettingValueChanged(USettingUITypeResolver* InSetting)
{
	auto* ScalarResolver{ Cast<USettingUITypeResolver_Scalar>(InSetting) };
	if (ensure(ScalarResolver))
	{
		const auto CurrentValue{ ScalarResolver->GetSettingValue() };

		Slider_SettingValue->SetValue(CurrentValue);
		Spin_SettingValue->SetValue(CurrentValue);
	}

	Super::HandleSettingValueChanged(InSetting);
}

void USettingUIListEntry_Scalar::HandleSettingOptionChanged(USettingUITypeResolver* InSetting)
{
	auto* ScalarResolver{ Cast<USettingUITypeResolver_Scalar>(InSetting) };
	if (ensure(ScalarResolver))
	{
		const auto Step{ ScalarResolver->GetStep() };
		const auto FractionDigits{ ScalarResolver->GetFractionDigits() };
		const auto Max{ ScalarResolver->GetMaxValue() };
		const auto Min{ ScalarResolver->GetMinValue() };

		Slider_SettingValue->SetMaxValue(Max);
		Slider_SettingValue->SetMinValue(Min);
		Slider_SettingValue->SetStepSize(Step);

		Spin_SettingValue->SetMaxFractionalDigits(FractionDigits);
		Spin_SettingValue->SetMinFractionalDigits(0);
		Spin_SettingValue->SetMaxSliderValue(Max);
		Spin_SettingValue->SetMaxValue(Max);
		Spin_SettingValue->SetMinSliderValue(Min);
		Spin_SettingValue->SetMinValue(Min);
		Spin_SettingValue->SetDelta(Step);
	}

	Super::HandleSettingOptionChanged(InSetting);
}

void USettingUIListEntry_Scalar::HandleSpinValueCommit(float NewValue, ETextCommit::Type CommitMethod)
{
	SetSettingValue(NewValue);
}

void USettingUIListEntry_Scalar::HandleSliderValueChange(float NewValue)
{
	Spin_SettingValue->SetValue(NewValue);
}

void USettingUIListEntry_Scalar::HandleSliderValueCommit()
{
	SetSettingValue(Slider_SettingValue->GetValue());
}


void USettingUIListEntry_Scalar::SetSettingValue(float NewValue)
{
	auto* ScalarResolver{ GetResolver<USettingUITypeResolver_Scalar>() };
	if (ensure(ScalarResolver))
	{
		ScalarResolver->SetSettingValue(NewValue);
	}
}
