// Copyright (C) 2024 owoDra

#pragma once

#include "SettingUIOptionTypes.generated.h"

class USettingUITypeResolver;
class UGSCSubsystem;


/**
 * Data for accessing configuration items
 */
USTRUCT(BlueprintType)
struct FSettingUIOptionAccessor
{
	GENERATED_BODY()
public:
	FSettingUIOptionAccessor() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftClassPtr<USettingUITypeResolver> Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftClassPtr<UGSCSubsystem> Source;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName GetterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName SetterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName OptionGetterName;

};


/**
 * Row data for setting options to be displayed in the settings UI
 */
USTRUCT(BlueprintType)
struct GAUISETTING_API FSettingUIOption : public FTableRowBase
{
	GENERATED_BODY()
public:
	FSettingUIOption() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FText> Categories;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSet<FName> DependentSettings;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ShowOnlyInnerProperties))
	FSettingUIOptionAccessor Accessor;

};
