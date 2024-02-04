// Copyright (C) 2024 owoDra

#pragma once

#include "Type/SettingUIEditTypes.h"

#include "SettingUIEditCondition.generated.h"

class USettingUITypeResolver;


/**
 * Class to determine if this setting option is editable
 */
UCLASS(Abstract, BlueprintType, NotBlueprintable)
class GAUISETTING_API USettingUIEditCondition : public UObject
{
	GENERATED_BODY()
public:
	USettingUIEditCondition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	////////////////////////////////////////////////////////////////////////
	// Initialization
protected:
	UPROPERTY()
	TObjectPtr<USettingUITypeResolver> OwnerSetting{ nullptr };

public:
	virtual void InitializeEditCondition(USettingUITypeResolver* InOwnerSetting);
	virtual void DeinitializeEditCondition();


	////////////////////////////////////////////////////////////////////////
	// Edit Condition
public:
	virtual FSettingUIEditableState ComputeEditableState() const PURE_VIRTUAL(, return FSettingUIEditableState::NotEditable;);
	
};
