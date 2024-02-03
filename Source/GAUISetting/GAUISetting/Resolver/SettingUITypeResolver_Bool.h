// Copyright (C) 2024 owoDra

#pragma once

#include "SettingUITypeResolver.h"

#include "SettingUITypeResolver_Bool.generated.h"


/**
 * 
 */
UCLASS(meta = (DisplayName = "Bool Type Resolver"))
class GAUISETTING_API USettingUITypeResolver_Bool : public USettingUITypeResolver
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Bool(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#if WITH_EDITOR
public:
	UFUNCTION()
	static bool GetterTemplate() { return false; }

	UFUNCTION()
	static void SetterTemplate(bool Arg) {}

	UFUNCTION()
	static TArray<bool> OptionGetterTemplate() { return TArray<bool>(); }
#endif

};
