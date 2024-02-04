// Copyright (C) 2024 owoDra

#pragma once

#include "Factories/Factory.h"

#include "SettingUITableFactory.generated.h"


UCLASS()
class USettingUITableFactory : public UFactory
{
	GENERATED_BODY()
public:
	USettingUITableFactory(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

};
