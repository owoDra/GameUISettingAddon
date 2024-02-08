// Copyright (C) 2024 owoDra

#pragma once

#include "Subsystems/LocalPlayerSubsystem.h"

#include "GameplayTagContainer.h"

#include "SettingUISubsystem.generated.h"

class UGSCGameUserSettings;
class USettingUITypeResolver;
class USettingUICustomRegister;
class UDataTable;


/**
 * Currently registered setting table data
 */
USTRUCT()
struct FRegisteredSettingUITable
{
	GENERATED_BODY()
public:
	FRegisteredSettingUITable() = default;

public:
	UPROPERTY()
	TMap<FName, TObjectPtr<USettingUITypeResolver>> Row;

};


/**
 * Subsystems that manage setting options that can be displayed in the UI
 */
UCLASS()
class GAUISETTING_API USettingUISubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
public:
	USettingUISubsystem() {}

	////////////////////////////////////////////////////////////////////////
	// Initialization
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

protected:
	virtual void LoadStartupSettings();


	////////////////////////////////////////////////////////////////////////
	// Setting Tables
protected:
	//
	// Mapping list for each added data table of all currently registered settings
	//
	UPROPERTY(Transient)
	TMap<FGameplayTag, FRegisteredSettingUITable> SettingTables;

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Setting Table", meta = (GameplayTagFilter = "UI.SettingTable"))
	virtual void AddSettingTable(FGameplayTag TableTag, UPARAM(meta = (RowType = "SettingUIOption")) const UDataTable* InSettingTable);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Setting Table", meta = (GameplayTagFilter = "UI.SettingTable"))
	virtual void AddSettingCustomTable(FGameplayTag TableTag, const USettingUICustomRegister* InCustomRegister);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Setting Table", meta = (GameplayTagFilter = "UI.SettingTable"))
	virtual void RemoveSettingTable(FGameplayTag TableTag);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Setting Table")
	virtual void RemoveAllSettingTable();

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Setting Table", meta = (GameplayTagFilter = "UI.SettingTable"))
	virtual void GetTableSettings(FGameplayTag TableTag, TArray<USettingUITypeResolver*>& OutArray) const;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Setting Table")
	virtual void NotifySettingsUpdate(const TSet<FName>& SettingNames);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Setting Table")
	virtual void NotifyAllSettingsUpdate();

};
