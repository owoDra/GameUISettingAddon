// Copyright (C) 2024 owoDra

#pragma once

#include "Blueprint/UserWidget.h"

#include "SettingUIDetailExtension.generated.h"

class USettingUITypeResolver;


/**
 * Special detail display widget classes specific to the type of configuration item
 */
UCLASS(Abstract, meta = (DisableNativeTick))
class GAUISETTING_API USettingUIDetailExtension : public UUserWidget
{
	GENERATED_BODY()
public:
	USettingUIDetailExtension(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	///////////////////////////////////////////////////////////
	// Initialization
protected:
	UPROPERTY(Transient)
	TWeakObjectPtr<USettingUITypeResolver> CurrentSetting;

public:
	void SetSetting(USettingUITypeResolver* InSetting);
	
protected:
	virtual void NativeSettingAssigned(USettingUITypeResolver* InSetting);
	virtual void NativeSettingValueChanged(USettingUITypeResolver* InSetting);

	UFUNCTION(BlueprintImplementableEvent)
	void OnSettingAssigned(USettingUITypeResolver* InSetting);

	UFUNCTION(BlueprintImplementableEvent)
	void OnSettingValueChanged(USettingUITypeResolver* InSetting);

};
