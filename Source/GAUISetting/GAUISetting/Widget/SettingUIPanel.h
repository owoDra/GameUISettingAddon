// Copyright (C) 2024 owoDra

#pragma once

#include "CommonUserWidget.h"

#include "SettingUIPanel.generated.h"

class USettingUIListView;
class USettingUIDetailView;
class USettingUITypeResolver;


/**
 * Base widget for the part of the Setting UI that displays setting options, etc.
 * 
 * Tips:
 *	Mainly performs interaction processing to items in the settings list and updates the list
 */
UCLASS(Abstract)
class GAUISETTING_API USettingUIPanel : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	USettingUIPanel(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//////////////////////////////////////////////////////////////////////////////////
	// Initialization
public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	/**
	 * Focus transitioning to subwidgets for the gamepad
	 */
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;


	//////////////////////////////////////////////////////////////////////////////////
	// List View
protected:
	void HandleSettingItemHoveredChanged(UObject* Item, bool bHovered);
	void HandleSettingItemSelectionChanged(UObject* Item);


	//////////////////////////////////////////////////////////////////////////////////
	// Detail View
protected:
	void FillSettingDetails(USettingUITypeResolver* InSetting);


	///////////////////////////////////////////////////////////
	// Widget bounds
private:	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<USettingUIListView> ListView_Settings;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<USettingUIDetailView> DetailView_Settings;

};
