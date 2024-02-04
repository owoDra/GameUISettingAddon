// Copyright (C) 2024 owoDra

#pragma once

#include "Engine/DataAsset.h"

#include "SettingUIDetailVisualData.generated.h"

class USettingUIDetailExtension;
class USettingUITypeResolver;


/**
 * Detail extension widget class definition data according to the ResolverType of the setting option
 */
USTRUCT(BlueprintType)
struct FExtensionDef_ResolverType
{
	GENERATED_BODY()
public:
	FExtensionDef_ResolverType() = default;

public:
	UPROPERTY(EditAnywhere, Category = Extensions)
	TArray<TSoftClassPtr<USettingUIDetailExtension>> Extensions;
};


/**
 * Detail extension widget class definition data according to the setting name of the setting option
 */
USTRUCT(BlueprintType)
struct FExtensionDef_SettingName
{
	GENERATED_BODY()
public:
	FExtensionDef_SettingName() = default;

public:
	UPROPERTY(EditAnywhere, Category = Extensions)
	bool bIncludeClassDefaultExtensions{ false };

	UPROPERTY(EditAnywhere, Category = Extensions)
	TArray<TSoftClassPtr<USettingUIDetailExtension>> Extensions;

};


/**
 * Definition data for a wedget that displays detailed information for each type of setting option
 */
UCLASS(BlueprintType, Const)
class GAUISETTING_API USettingUIDetailVisualData : public UDataAsset
{
	GENERATED_BODY()
public:
	USettingUIDetailVisualData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Detail Extension", meta = (ForceInlineRow, AllowAbstract))
	TMap<TSubclassOf<USettingUITypeResolver>, FExtensionDef_ResolverType> ExtensionsForClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Detail Extension", meta = (ForceInlineRow, GetOptions = "GAUISetting.SettingUITable.GetDefinedSettingNames"))
	TMap<FName, FExtensionDef_SettingName> ExtensionsForName;

public:
	virtual TArray<TSoftClassPtr<USettingUIDetailExtension>> GatherDetailExtensions(const USettingUITypeResolver* InSetting) const;
	
};
