// Copyright (C) 2024 owoDra

#pragma once

#include "Factories/Factory.h"

#include "SettingUIListVisualDataFactory.generated.h"


UCLASS(hidecategories = Object, MinimalAPI)
class USettingUIListVisualDataFactory : public UFactory
{
	GENERATED_BODY()
public:
	USettingUIListVisualDataFactory(const FObjectInitializer& ObjectInitializer= FObjectInitializer::Get());

public:
	virtual bool ShouldShowInNewMenu() const override { return true; }

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

};

