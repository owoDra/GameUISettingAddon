// Copyright (C) 2024 owoDra

#pragma once

#include "GameplayTagContainer.h"

#include "SettingUIOptionTypes.generated.h"

class USettingUITypeResolver;
class USettingUIEditCondition;
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
	//
	// Parameter type of setting option
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<USettingUITypeResolver> Type;

	//
	// Class in which setting option parameter are stored
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGSCSubsystem> Source;

	//
	// Getter function name for setting option parameter
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName GetterName;

	//
	// Setter function name for setting option parameter
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName SetterName;

	//
	// Getter function name for enumerated values of setting option parameter
	//
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
	//
	// Name displayed on the UI of the setting option
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Name;

	//
	// Description displayed on the UI of the setting option
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Description;

	//
	// Categories displayed on the UI of the setting option
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Category;

	//
	// Platform Trait Tags required to edit this configuration item.
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTagContainer RequestTraitTags;

	//
	// Setting to be updated when this value is changed.
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (GetOptions = "GAUISetting.SettingUITable.GetDefinedSettingNames"))
	TSet<FName> DependentSettings;

	//
	// Class to determine if this setting option is editable
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<USettingUIEditCondition> EditCondition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ShowOnlyInnerProperties))
	FSettingUIOptionAccessor Accessor;

};
