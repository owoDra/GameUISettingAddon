// Copyright (C) 2024 owoDra

#include "SettingUIPanel.h"

#include "Widget/ListView/SettingUIListView.h"
#include "Widget/DetailView/SettingUIDetailView.h"
#include "Resolver/SettingUITypeResolver.h"

#include "CommonInputSubsystem.h"
#include "CommonInputTypeEnum.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUIPanel)

/////////////////////////////////////////////////////////////////////

USettingUIPanel::USettingUIPanel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetIsFocusable(true);
}


void USettingUIPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ListView_Settings->OnItemIsHoveredChanged().AddUObject(this, &ThisClass::HandleSettingItemHoveredChanged);
	ListView_Settings->OnItemSelectionChanged().AddUObject(this, &ThisClass::HandleSettingItemSelectionChanged);
}

void USettingUIPanel::NativeConstruct()
{
	Super::NativeConstruct();
}

void USettingUIPanel::NativeDestruct()
{
	Super::NativeDestruct();
}

FReply USettingUIPanel::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	const UCommonInputSubsystem* InputSubsystem = GetInputSubsystem();
	if (InputSubsystem && InputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
	{
		if (TSharedPtr<SWidget> PrimarySlateWidget = ListView_Settings->GetCachedWidget())
		{
			ListView_Settings->NavigateToIndex(0);
			ListView_Settings->SetSelectedIndex(0);

			return FReply::Handled();
		}
	}

	return FReply::Unhandled();
}


void USettingUIPanel::HandleSettingItemHoveredChanged(UObject* Item, bool bHovered)
{
	if (bHovered)
	{
		FillSettingDetails(Cast<USettingUITypeResolver>(Item));
	}
}

void USettingUIPanel::HandleSettingItemSelectionChanged(UObject* Item)
{
	FillSettingDetails(Cast<USettingUITypeResolver>(Item));
}


void USettingUIPanel::FillSettingDetails(USettingUITypeResolver* InSetting)
{
	if (DetailView_Settings && InSetting)
	{
		DetailView_Settings->FillSettingDetails(InSetting);
	}
}
