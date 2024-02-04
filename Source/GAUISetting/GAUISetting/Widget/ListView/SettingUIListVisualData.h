// Copyright (C) 2024 owoDra

#pragma once

#include "Engine/DataAsset.h"

#include "SettingUIListVisualData.generated.h"

class USettingUITypeResolver;
class USettingUIListEntry;


/**
 * Definition data for a wedget that displays list entry for each type of setting option
 */
UCLASS(BlueprintType, Const)
class GAUISETTING_API USettingUIListVisualData : public UDataAsset
{
	GENERATED_BODY()
public:
	USettingUIListVisualData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(EditDefaultsOnly, Category = "List View", meta = (ForceInlineRow, AllowAbstract))
	TMap<TSubclassOf<USettingUITypeResolver>, TSubclassOf<USettingUIListEntry>> EntryWidgetForClass;

	UPROPERTY(EditDefaultsOnly, Category = "List View", meta = (ForceInlineRow, GetOptions = "GAUISetting.SettingUITable.GetDefinedSettingNames"))
	TMap<FName, TSubclassOf<USettingUIListEntry>> EntryWidgetForName;
	
public:
	TSubclassOf<USettingUIListEntry> GetEntryForSetting(USettingUITypeResolver* InSetting) const;

protected:
	virtual TSubclassOf<USettingUIListEntry> GetCustomEntryForSetting(USettingUITypeResolver* InSetting) const;

};
