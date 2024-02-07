// Copyright (C) 2024 owoDra

#include "SettingUITypeResolver_Scalar.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUITypeResolver_Scalar)

//////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Scalar

USettingUITypeResolver_Scalar::USettingUITypeResolver_Scalar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


//////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Scalar_Float

USettingUITypeResolver_Scalar_Float::USettingUITypeResolver_Scalar_Float(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void USettingUITypeResolver_Scalar_Float::SetSettingValue(float NewValue)
{
	SetPropertyValue<float>(NewValue);
}

float USettingUITypeResolver_Scalar_Float::GetSettingValue() const
{
	auto Result{ 0.0f };
	GetPropertyValue<float>(Result);
	return Result;
}


//////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Scalar_Int

USettingUITypeResolver_Scalar_Int::USettingUITypeResolver_Scalar_Int(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void USettingUITypeResolver_Scalar_Int::SetSettingValue(float NewValue)
{
	SetPropertyValue<int32>(NewValue);
}

float USettingUITypeResolver_Scalar_Int::GetSettingValue() const
{
	int32 Result{ 0 };
	GetPropertyValue<int32>(Result);
	return Result;
}


//////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Scalar_Byte

USettingUITypeResolver_Scalar_Byte::USettingUITypeResolver_Scalar_Byte(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void USettingUITypeResolver_Scalar_Byte::SetSettingValue(float NewValue)
{
	SetPropertyValue<uint8>(NewValue);
}

float USettingUITypeResolver_Scalar_Byte::GetSettingValue() const
{
	uint8 Result{ 0 };
	GetPropertyValue<uint8>(Result);
	return Result;
}
