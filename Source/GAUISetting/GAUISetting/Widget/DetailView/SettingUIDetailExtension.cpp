// Copyright (C) 2024 owoDra

#include "SettingUIDetailExtension.h"

#include "Resolver/SettingUITypeResolver.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUIDetailExtension)

//////////////////////////////////////////////////////////////////////////////

USettingUIDetailExtension::USettingUIDetailExtension(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void USettingUIDetailExtension::SetSetting(USettingUITypeResolver* InSetting)
{
	NativeSettingAssigned(InSetting);
}

void USettingUIDetailExtension::NativeSettingAssigned(USettingUITypeResolver* InSetting)
{
	if (CurrentSetting.IsValid())
	{
		CurrentSetting->OnPropertyValueChange.RemoveAll(this);
	}

	CurrentSetting = InSetting;
	CurrentSetting->OnPropertyValueChange.AddUObject(this, &ThisClass::NativeSettingValueChanged);

	OnSettingAssigned(InSetting);
}

void USettingUIDetailExtension::NativeSettingValueChanged(USettingUITypeResolver* InSetting)
{
	OnSettingValueChanged(InSetting);
}
