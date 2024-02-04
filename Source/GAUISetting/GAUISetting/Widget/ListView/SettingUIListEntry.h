// Copyright (C) 2024 owoDra

#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "CommonUserWidget.h"

#include "Type/SettingUIEditTypes.h"

#include "SettingUIListEntry.generated.h"

class USettingUITypeResolver;
class UCommonTextBlock;


/**
 * Base class for entry widgets for setting lists
 */
UCLASS(Abstract, meta = (DisableNativeTick))
class GAUISETTING_API USettingUIListEntry : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	USettingUIListEntry(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//////////////////////////////////////////////////////////////////
	// Initialization
protected:
	UPROPERTY()
	TWeakObjectPtr<USettingUITypeResolver> Setting;

public:
	virtual void SetSetting(USettingUITypeResolver* InSetting);

protected:
	virtual void NativeOnEntryReleased() override;

	virtual void HandleSettingValueChanged(USettingUITypeResolver* InSetting);
	virtual void HandleEditableStateChanged(USettingUITypeResolver* InSetting, const FSettingUIEditableState& InEditableState);

	UFUNCTION(BlueprintImplementableEvent, Category = "Setting")
	void OnSettingValueChanged(USettingUITypeResolver* InSetting);

	UFUNCTION(BlueprintImplementableEvent, Category = "Setting")
	void OnEditableStateChanged(USettingUITypeResolver* InSetting, const FSettingUIEditableState& InEditableState);


	//////////////////////////////////////////////////////////////////
	// Forcus
protected:
	/**
	 * Focus transitioning to subwidgets for the gamepad
	 */
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	UFUNCTION(BlueprintImplementableEvent)
	UWidget* GetPrimaryGamepadFocusWidget();


	//////////////////////////////////////////////////////////////////
	// Widget Bounds
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UUserWidget> Background;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonTextBlock> Text_SettingName;

};
