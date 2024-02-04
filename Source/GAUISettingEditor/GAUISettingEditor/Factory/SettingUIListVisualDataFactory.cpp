// Copyright (C) 2024 owoDra

#include "SettingUIListVisualDataFactory.h"

#include "Widget/ListView/SettingUIListVisualData.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUIListVisualDataFactory)


USettingUIListVisualDataFactory::USettingUIListVisualDataFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = USettingUIListVisualData::StaticClass();

	bCreateNew = true;
	bEditorImport = false;
	bEditAfterNew = true;
}

UObject* USettingUIListVisualDataFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<USettingUIListVisualData>(InParent, Name, Flags);
}
