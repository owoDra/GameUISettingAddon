// Copyright (C) 2024 owoDra

#include "SettingUIDetailVisualDataFactory.h"

#include "Widget/DetailView/SettingUIDetailVisualData.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUIDetailVisualDataFactory)


USettingUIDetailVisualDataFactory::USettingUIDetailVisualDataFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = USettingUIDetailVisualData::StaticClass();

	bCreateNew = true;
	bEditorImport = false;
	bEditAfterNew = true;
}

UObject* USettingUIDetailVisualDataFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<USettingUIDetailVisualData>(InParent, Name, Flags);
}
