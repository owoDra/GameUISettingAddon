// Copyright (C) 2024 owoDra

#include "SettingUIEditCondition.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUIEditCondition)


USettingUIEditCondition::USettingUIEditCondition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void USettingUIEditCondition::InitializeEditCondition(USettingUITypeResolver* InOwnerSetting)
{
	OwnerSetting = InOwnerSetting;
}

void USettingUIEditCondition::DeinitializeEditCondition()
{
}
