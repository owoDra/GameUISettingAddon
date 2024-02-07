// Copyright (C) 2024 owoDra

#include "SettingUITypeResolver_Switch.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUITypeResolver_Switch)

//////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Switch

USettingUITypeResolver_Switch::USettingUITypeResolver_Switch(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


//////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Switch_Bool

USettingUITypeResolver_Switch_Bool::USettingUITypeResolver_Switch_Bool(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TrueText = FText(NSLOCTEXT("SettingUI", "BoolSwitchTrueText", "On"));
	FalseText = FText(NSLOCTEXT("SettingUI", "BoolSwitchFalseText", "Off"));
}


void USettingUITypeResolver_Switch_Bool::SetSettingValue(int32 NewValue)
{
	SetPropertyValue<bool>(NewValue > 0);
}

int32 USettingUITypeResolver_Switch_Bool::GetSettingValue() const
{
	auto bResult{ false };

	GetPropertyValue<bool>(bResult);

	return bResult ? 1 : 0;
}


TArray<FText> USettingUITypeResolver_Switch_Bool::GetOptionDisplayTexts() const
{
	return { /*Index 0 = */ FalseText, /*Index 1 = */ TrueText };
}


//////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Switch_Float

USettingUITypeResolver_Switch_Float::USettingUITypeResolver_Switch_Float(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OptionFormat = FText(NSLOCTEXT("SettingUI", "FloatSwitchTextFormat", "{Value}"));
}


void USettingUITypeResolver_Switch_Float::NotifyPropertyOptionChange()
{
	OptionDisplayTexts.Reset();
	OptionValues.Reset();

	if (GetPropertyOptions(OptionValues))
	{
		const auto bHasFormat{ OptionFormat.IsEmpty() };

		for (const auto& OptionValue : OptionValues)
		{
			if (bHasFormat)
			{
				OptionDisplayTexts.Add(FText::Format(OptionFormat, OptionValue));
			}
			else
			{
				OptionDisplayTexts.Add(FText::Format(NSLOCTEXT("SettingUI", "FloatSwitchTextFormat", "{Value}"), OptionValue));
			}
		}
	}

	Super::NotifyPropertyOptionChange();
}

void USettingUITypeResolver_Switch_Float::SetSettingValue(int32 NewValue)
{
	if (ensure(OptionValues.IsValidIndex(NewValue)))
	{
		SetPropertyValue<float>(OptionValues[NewValue]);
	}
}

int32 USettingUITypeResolver_Switch_Float::GetSettingValue() const
{
	auto Result{ 0.0f };
	GetPropertyValue<float>(Result);
	return OptionValues.Find(Result);
}


TArray<FText> USettingUITypeResolver_Switch_Float::GetOptionDisplayTexts() const
{
	return OptionDisplayTexts;
}


//////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Switch_Double

USettingUITypeResolver_Switch_Double::USettingUITypeResolver_Switch_Double(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OptionFormat = FText(NSLOCTEXT("SettingUI", "DoubleSwitchTextFormat", "{Value}"));
}


void USettingUITypeResolver_Switch_Double::NotifyPropertyOptionChange()
{
	OptionDisplayTexts.Reset();
	OptionValues.Reset();

	if (GetPropertyOptions(OptionValues))
	{
		const auto bHasFormat{ OptionFormat.IsEmpty() };

		for (const auto& OptionValue : OptionValues)
		{
			if (bHasFormat)
			{
				OptionDisplayTexts.Add(FText::Format(OptionFormat, OptionValue));
			}
			else
			{
				OptionDisplayTexts.Add(FText::Format(NSLOCTEXT("SettingUI", "DoubleSwitchTextFormat", "{Value}"), OptionValue));
			}
		}
	}

	Super::NotifyPropertyOptionChange();
}

void USettingUITypeResolver_Switch_Double::SetSettingValue(int32 NewValue)
{
	if (ensure(OptionValues.IsValidIndex(NewValue)))
	{
		SetPropertyValue<double>(OptionValues[NewValue]);
	}
}

int32 USettingUITypeResolver_Switch_Double::GetSettingValue() const
{
	auto Result{ 0.0 };
	GetPropertyValue<double>(Result);
	return OptionValues.Find(Result);
}


TArray<FText> USettingUITypeResolver_Switch_Double::GetOptionDisplayTexts() const
{
	return OptionDisplayTexts;
}


//////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Switch_Int

USettingUITypeResolver_Switch_Int::USettingUITypeResolver_Switch_Int(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OptionFormat = FText(NSLOCTEXT("SettingUI", "IntSwitchTextFormat", "{Value}"));
}


void USettingUITypeResolver_Switch_Int::NotifyPropertyOptionChange()
{
	OptionDisplayTexts.Reset();
	OptionValues.Reset();

	if (GetPropertyOptions(OptionValues))
	{
		const auto bHasFormat{ OptionFormat.IsEmpty() };

		for (const auto& OptionValue : OptionValues)
		{
			if (bHasFormat)
			{
				OptionDisplayTexts.Add(FText::Format(OptionFormat, OptionValue));
			}
			else
			{
				OptionDisplayTexts.Add(FText::Format(NSLOCTEXT("SettingUI", "IntSwitchTextFormat", "{Value}"), OptionValue));
			}
		}
	}

	Super::NotifyPropertyOptionChange();
}

void USettingUITypeResolver_Switch_Int::SetSettingValue(int32 NewValue)
{
	if (ensure(OptionValues.IsValidIndex(NewValue)))
	{
		SetPropertyValue<int32>(OptionValues[NewValue]);
	}
}

int32 USettingUITypeResolver_Switch_Int::GetSettingValue() const
{
	auto Result{ 0 };
	GetPropertyValue<int32>(Result);
	return OptionValues.Find(Result);
}


TArray<FText> USettingUITypeResolver_Switch_Int::GetOptionDisplayTexts() const
{
	return OptionDisplayTexts;
}


//////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Switch_String

USettingUITypeResolver_Switch_String::USettingUITypeResolver_Switch_String(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void USettingUITypeResolver_Switch_String::NotifyPropertyOptionChange()
{
	OptionDisplayTexts.Reset();
	OptionValues.Reset();

	if (GetPropertyOptions(OptionValues))
	{
		for (const auto& OptionValue : OptionValues)
		{
			OptionDisplayTexts.Add(FText::FromString(OptionValue));
		}
	}

	Super::NotifyPropertyOptionChange();
}

void USettingUITypeResolver_Switch_String::SetSettingValue(int32 NewValue)
{
	if (ensure(OptionValues.IsValidIndex(NewValue)))
	{
		SetPropertyValue<FString>(OptionValues[NewValue]);
	}
}

int32 USettingUITypeResolver_Switch_String::GetSettingValue() const
{
	FString Result;
	GetPropertyValue<FString>(Result);
	return OptionValues.Find(Result);
}


TArray<FText> USettingUITypeResolver_Switch_String::GetOptionDisplayTexts() const
{
	return OptionDisplayTexts;
}


//////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Switch_Byte

USettingUITypeResolver_Switch_Byte::USettingUITypeResolver_Switch_Byte(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OptionFormat = FText(NSLOCTEXT("SettingUI", "ByteSwitchTextFormat", "{Value}"));
}


void USettingUITypeResolver_Switch_Byte::NotifyPropertyOptionChange()
{
	OptionDisplayTexts.Reset();
	OptionValues.Reset();

	if (GetPropertyOptions(OptionValues))
	{
		const auto bHasFormat{ OptionFormat.IsEmpty() };

		for (const auto& OptionValue : OptionValues)
		{
			if (bHasFormat)
			{
				OptionDisplayTexts.Add(FText::Format(OptionFormat, OptionValue));
			}
			else
			{
				OptionDisplayTexts.Add(FText::Format(NSLOCTEXT("SettingUI", "ByteSwitchTextFormat", "{Value}"), OptionValue));
			}
		}
	}

	Super::NotifyPropertyOptionChange();
}

void USettingUITypeResolver_Switch_Byte::SetSettingValue(int32 NewValue)
{
	if (ensure(OptionValues.IsValidIndex(NewValue)))
	{
		SetPropertyValue<uint8>(OptionValues[NewValue]);
	}
}

int32 USettingUITypeResolver_Switch_Byte::GetSettingValue() const
{
	uint8 Result;
	GetPropertyValue<uint8>(Result);
	return OptionValues.Find(Result);
}


TArray<FText> USettingUITypeResolver_Switch_Byte::GetOptionDisplayTexts() const
{
	return OptionDisplayTexts;
}



//////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Switch_Enum

USettingUITypeResolver_Switch_Enum::USettingUITypeResolver_Switch_Enum(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void USettingUITypeResolver_Switch_Enum::NotifyPropertyOptionChange()
{
	OptionDisplayTexts.Reset();
	OptionValues.Reset();

	const auto* Enum{ GetPropertyAsEnum() };
	if (ensure(Enum))
	{
		const auto NumEnum{ Enum->NumEnums() - 1 };

		for (auto Idx{ 0 }; Idx < NumEnum; ++Idx)
		{
			if (!Enum->HasMetaData(TEXT("Hidden"), Idx))
			{
				OptionDisplayTexts.Add(Enum->GetDisplayNameTextByIndex(Idx));
				OptionValues.Add(Idx);
			}
		}
	}

	Super::NotifyPropertyOptionChange();
}

const UEnum* USettingUITypeResolver_Switch_Enum::GetPropertyAsEnum() const
{
	auto* Container{ GetSource() };
	auto* Function{ Container ? Container->FindFunction(Data.Accessor.GetterName) : nullptr };
	auto* EnumProperty{ Function ? CastField<FEnumProperty>(Function->GetReturnProperty()) : nullptr };
	auto* Enum{ EnumProperty ? EnumProperty->GetEnum() : nullptr};

	return Enum;
}

void USettingUITypeResolver_Switch_Enum::SetSettingValue(int32 NewValue)
{
	if (ensure(OptionValues.IsValidIndex(NewValue)))
	{
		SetPropertyValue<uint8>(OptionValues[NewValue]);
	}
}

int32 USettingUITypeResolver_Switch_Enum::GetSettingValue() const
{
	uint8 Result;
	GetPropertyValue<uint8>(Result);
	return OptionValues.Find(Result);
}


TArray<FText> USettingUITypeResolver_Switch_Enum::GetOptionDisplayTexts() const
{
	return OptionDisplayTexts;
}
