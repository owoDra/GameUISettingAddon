// Copyright (C) 2023 owoDra

#pragma once

#include "Widget/ListView/Entry/SettingUIListEntry.h"

#include "SettingUIListEntry_Switch.generated.h"

class UCommonTextBlock;
class UCommonButtonBase;
class UCommonRotator;

/**
 * List entry class for Bool type configuration items
 */
UCLASS(Abstract, Blueprintable, meta = (DisplayName = "Switch Setting Entry"))
class GAUISETTING_API USettingUIListEntry_Switch : public USettingUIListEntry
{
	GENERATED_BODY()
public:
	USettingUIListEntry_Switch(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	////////////////////////////////////////////////////////////
	// Initialization
protected:
	virtual void NativeOnInitialized() override;


	////////////////////////////////////////////////////////////
	// Change Setting
protected:
	virtual void HandleSettingValueChanged(USettingUITypeResolver* InSetting) override;
	virtual void HandleSettingOptionChanged(USettingUITypeResolver* InSetting) override;
	 
	void HandleOptionDecrease();
	void HandleOptionIncrease();
	void HandleRotatorChangedValue(int32 Value, bool bUserInitiated);

	virtual void SetSettingValue(int32 NewValue);


	////////////////////////////////////////////////////////////
	// Widget Bounds
private:	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonRotator> Rotator_SettingValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonButtonBase> Button_Decrease;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonButtonBase> Button_Increase;

};