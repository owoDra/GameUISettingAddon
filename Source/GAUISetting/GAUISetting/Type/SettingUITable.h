// Copyright (C) 2024 owoDra

#pragma once

#include "Engine/DataTable.h"

#include "SettingUITable.generated.h"


/**
 * Data table defining setting options that can be displayed in the UI
 */
UCLASS(BlueprintType)
class GAUISETTING_API USettingUITable : public UDataTable
{
	GENERATED_BODY()
public:
	USettingUITable();
	virtual ~USettingUITable() = default;

#if WITH_EDITOR
public:
	UFUNCTION()
	static TArray<FName> GetDefinedSettingNames();
#endif
};
