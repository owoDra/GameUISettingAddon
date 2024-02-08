// Copyright (C) 2024 owoDra

#pragma once

#include "Engine/DataAsset.h"

#include "SettingUISubsystem.h"

#include "SettingUICustomRegister.generated.h"

class USettingUITypeResolver;


/**
 * Class to be used when setting items need to be registered by methods other than data tables
 * 
 * For example:
 *	Can be used to automatically create setting options based on registered input actions
 */
UCLASS(Abstract, Blueprintable, BlueprintType, Const)
class GAUISETTING_API USettingUICustomRegister : public UDataAsset
{
	GENERATED_BODY()
public:
	USettingUICustomRegister(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual FRegisteredSettingUITable CreateTable(USettingUISubsystem* Subsystem) const PURE_VIRTUAL(, return FRegisteredSettingUITable(););

};
