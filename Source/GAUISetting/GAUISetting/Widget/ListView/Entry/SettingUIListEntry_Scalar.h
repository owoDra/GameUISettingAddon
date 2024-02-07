// Copyright (C) 2023 owoDra

#pragma once

#include "Widget/ListView/Entry/SettingUIListEntry.h"

#include "SettingUIListEntry_Scalar.generated.h"

class UAnalogSlider;
class USpinBox;


/**
 * List entry class for Bool type configuration items
 */
UCLASS(Abstract, Blueprintable, meta = (DisplayName = "Scalar Setting Entry"))
class GAUISETTING_API USettingUIListEntry_Scalar : public USettingUIListEntry
{
	GENERATED_BODY()
public:
	USettingUIListEntry_Scalar(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	////////////////////////////////////////////////////////////
	// Initialization
protected:
	virtual void NativeOnInitialized() override;


	////////////////////////////////////////////////////////////
	// Change Setting
protected:
	virtual void HandleSettingValueChanged(USettingUITypeResolver* InSetting) override;
	virtual void HandleSettingOptionChanged(USettingUITypeResolver* InSetting) override;
	 
	UFUNCTION()
	void HandleSpinValueCommit(float NewValue, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void HandleSliderValueChange(float NewValue);

	UFUNCTION()
	void HandleSliderValueCommit();

	virtual void SetSettingValue(float NewValue);


	////////////////////////////////////////////////////////////
	// Widget Bounds
private:	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UAnalogSlider> Slider_SettingValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<USpinBox> Spin_SettingValue;

};
