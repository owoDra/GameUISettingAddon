// Copyright (C) 2024 owoDra

#include "SettingUITableFactory.h"

#include "Type/SettingUITable.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUITableFactory)


USettingUITableFactory::USettingUITableFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = USettingUITable::StaticClass();
}


UObject* USettingUITableFactory::FactoryCreateNew(UClass* Class, UObject* Parent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(Class && Class->IsChildOf(USettingUITable::StaticClass()));
	return NewObject<USettingUITable>(Parent, Class, Name, Flags);
}
