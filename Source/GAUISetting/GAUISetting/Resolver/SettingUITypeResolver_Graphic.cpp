// Copyright (C) 2024 owoDra

#include "SettingUITypeResolver_Graphic.h"

#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUITypeResolver_Graphic)


///////////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Switch_Resolution

USettingUITypeResolver_Switch_Resolution::USettingUITypeResolver_Switch_Resolution(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void USettingUITypeResolver_Switch_Resolution::NotifyPropertyOptionChange()
{
	OptionDisplayTexts.Reset();
	OptionValues.Reset();

	UKismetSystemLibrary::GetSupportedFullscreenResolutions(OptionValues);
	for (const auto& Resolution : OptionValues)
	{
		OptionDisplayTexts.Add(FText::Format(NSLOCTEXT("SettingUI", "ResolutionTextFormat", "{0}×{1}"), Resolution.X, Resolution.Y));
	}

	Super::NotifyPropertyOptionChange();
}

void USettingUITypeResolver_Switch_Resolution::SetSettingValue(int32 NewValue)
{
	if (ensure(OptionValues.IsValidIndex(NewValue)))
	{
		auto* UserSettings{ UGameUserSettings::GetGameUserSettings() };
		if (ensure(UserSettings))
		{
			UserSettings->SetScreenResolution(OptionValues[NewValue]);
		}
	}
}

int32 USettingUITypeResolver_Switch_Resolution::GetSettingValue() const
{
	auto* UserSettings{ UGameUserSettings::GetGameUserSettings() };
	if (ensure(UserSettings))
	{
		return OptionValues.Find(UserSettings->GetScreenResolution());
	}

	return 0;
}


TArray<FText> USettingUITypeResolver_Switch_Resolution::GetOptionDisplayTexts() const
{
	return OptionDisplayTexts;
}


///////////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Switch_WindowMode

USettingUITypeResolver_Switch_WindowMode::USettingUITypeResolver_Switch_WindowMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OptionDisplayTexts = 
	{
		FText(NSLOCTEXT("SettingUI", "WindowModeFullscreen"			, "Fullscreen")),
		FText(NSLOCTEXT("SettingUI", "WindowModeWindowedFullscreen"	, "Borderless")),
		FText(NSLOCTEXT("SettingUI", "WindowModeWindowed"			, "Windowed"))
	};

	OptionValues =
	{
		EWindowMode::Fullscreen,
		EWindowMode::WindowedFullscreen,
		EWindowMode::Windowed,
	};
}


void USettingUITypeResolver_Switch_WindowMode::SetSettingValue(int32 NewValue)
{
	auto* UserSettings{ UGameUserSettings::GetGameUserSettings() };
	if (ensure(UserSettings))
	{
		UserSettings->SetFullscreenMode(OptionValues[NewValue]);
	}
}

int32 USettingUITypeResolver_Switch_WindowMode::GetSettingValue() const
{
	auto* UserSettings{ UGameUserSettings::GetGameUserSettings() };
	if (ensure(UserSettings))
	{
		return OptionValues.Find(UserSettings->GetFullscreenMode());
	}

	return 0;
}


TArray<FText> USettingUITypeResolver_Switch_WindowMode::GetOptionDisplayTexts() const
{
	return OptionDisplayTexts;
}


///////////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Switch_OverrallQuality

USettingUITypeResolver_Switch_OverrallQuality::USettingUITypeResolver_Switch_OverrallQuality(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OptionDisplayTexts =
	{
		FText(NSLOCTEXT("SettingUI", "WindowModeLow"		, "Low")),
		FText(NSLOCTEXT("SettingUI", "WindowModeMedium"		, "Medium")),
		FText(NSLOCTEXT("SettingUI", "WindowModeHigh"		, "High")),
		FText(NSLOCTEXT("SettingUI", "WindowModeEpic"		, "Higher")),
		FText(NSLOCTEXT("SettingUI", "WindowModeCinematic"	, "Ultra")),
		FText(NSLOCTEXT("SettingUI", "WindowModeCustom"		, "Custom"))
	};

	OptionValues =
	{
		 0,
		 1,
		 2,
		 3,
		 4,
		-1,
	};
}


void USettingUITypeResolver_Switch_OverrallQuality::SetSettingValue(int32 NewValue)
{
	auto* UserSettings{ UGameUserSettings::GetGameUserSettings() };
	if (ensure(UserSettings))
	{
		UserSettings->SetOverallScalabilityLevel(OptionValues[NewValue]);
		NotifyPropertyValueChange(true);
	}
}

int32 USettingUITypeResolver_Switch_OverrallQuality::GetSettingValue() const
{
	auto* UserSettings{ UGameUserSettings::GetGameUserSettings() };
	if (ensure(UserSettings))
	{
		return OptionValues.Find(UserSettings->GetOverallScalabilityLevel());
	}

	return 0;
}


TArray<FText> USettingUITypeResolver_Switch_OverrallQuality::GetOptionDisplayTexts() const
{
	return OptionDisplayTexts;
}


///////////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Switch_Quality

USettingUITypeResolver_Switch_Quality::USettingUITypeResolver_Switch_Quality(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OptionDisplayTexts =
	{
		FText(NSLOCTEXT("SettingUI", "WindowModeLow"		, "Low")),
		FText(NSLOCTEXT("SettingUI", "WindowModeMedium"		, "Medium")),
		FText(NSLOCTEXT("SettingUI", "WindowModeHigh"		, "High")),
		FText(NSLOCTEXT("SettingUI", "WindowModeEpic"		, "Higher")),
		FText(NSLOCTEXT("SettingUI", "WindowModeCinematic"	, "Ultra"))
	};

	OptionValues =
	{
		 0,
		 1,
		 2,
		 3,
		 4,
	};
}


void USettingUITypeResolver_Switch_Quality::SetSettingValue(int32 NewValue)
{
	SetPropertyValue<int32>(OptionValues[NewValue]);
}

int32 USettingUITypeResolver_Switch_Quality::GetSettingValue() const
{
	int32 Result{ 0 };
	GetPropertyValue<int32>(Result);
	return OptionValues.Find(Result);
}


TArray<FText> USettingUITypeResolver_Switch_Quality::GetOptionDisplayTexts() const
{
	return OptionDisplayTexts;
}


///////////////////////////////////////////////////////////////////////////
// USettingUITypeResolver_Switch_FrameRate

USettingUITypeResolver_Switch_FrameRate::USettingUITypeResolver_Switch_FrameRate(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OptionDisplayTexts =
	{
		FText(NSLOCTEXT("SettingUI", "FrameRateLimit30"		, "30 FPS")),
		FText(NSLOCTEXT("SettingUI", "FrameRateLimit60"		, "60 FPS")),
		FText(NSLOCTEXT("SettingUI", "FrameRateLimit75"		, "75 FPS")),
		FText(NSLOCTEXT("SettingUI", "FrameRateLimit120"	, "120 FPS")),
		FText(NSLOCTEXT("SettingUI", "FrameRateLimit144"	, "144 FPS")),
		FText(NSLOCTEXT("SettingUI", "FrameRateLimit165"	, "165 FPS")),
		FText(NSLOCTEXT("SettingUI", "FrameRateLimit240"	, "240 FPS")),
		FText(NSLOCTEXT("SettingUI", "FrameRateLimit300"	, "300 FPS")),
		FText(NSLOCTEXT("SettingUI", "FrameRateLimit0"		, "Unlimited"))
	};

	OptionValues =
	{
		30.0f,
		60.0f,
		75.0f,
		120.0f,
		144.0f,
		165.0f,
		240.0f,
		300.0f,
		0.0f
	};
}


void USettingUITypeResolver_Switch_FrameRate::SetSettingValue(int32 NewValue)
{
	auto* UserSettings{ UGameUserSettings::GetGameUserSettings() };
	if (ensure(UserSettings))
	{
		UserSettings->SetFrameRateLimit(OptionValues[NewValue]);
	}
}

int32 USettingUITypeResolver_Switch_FrameRate::GetSettingValue() const
{
	auto* UserSettings{ UGameUserSettings::GetGameUserSettings() };
	if (ensure(UserSettings))
	{
		return OptionValues.Find(UserSettings->GetFrameRateLimit());
	}

	return 0;
}

TArray<FText> USettingUITypeResolver_Switch_FrameRate::GetOptionDisplayTexts() const
{
	return OptionDisplayTexts;
}
