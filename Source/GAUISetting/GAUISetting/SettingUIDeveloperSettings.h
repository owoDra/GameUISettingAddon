// Copyright (C) 2024 owoDra

#pragma once

#include "Engine/DeveloperSettings.h"

#include "GameplayTagContainer.h"

#include "SettingUIDeveloperSettings.generated.h"


/**
 * Settings for a setting UI.
 */
UCLASS(Config = "Game", Defaultconfig, meta = (DisplayName = "Game UI: Setting Addon"))
class GAUISETTING_API USettingUIDeveloperSettings : public UDeveloperSettings
{
public:
	GENERATED_BODY()
public:
	USettingUIDeveloperSettings();

	///////////////////////////////////////////////
	// Startup Settings Registration
public:
	//
	// List of item definition tables for settings UI that are automatically loaded at game startup
	// 
	// Key	 : TableTag
	// Value : TableObject
	//
	UPROPERTY(Config, EditAnywhere, Category = "Startup", meta = (ForceInlineRow, RowType = "SettingUIOption", AllowedClasses = "/Script/GAUISetting.SettingUITable, /Script/GAUISetting.SettingUICustomRegister", Categories = "UI.SettingTable"))
	TMap<FGameplayTag, FSoftObjectPath> StartupSettingTables;

};

