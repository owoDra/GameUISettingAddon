// Copyright (C) 2024 owoDra

#include "SettingUIDetailView.h"

#include "Resolver/SettingUITypeResolver.h"
#include "SettingUIDetailVisualData.h"
#include "SettingUIDetailExtension.h"

#include "CommonRichTextBlock.h"
#include "CommonTextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUIDetailView)

//////////////////////////////////////////////////////////////////////

USettingUIDetailView::USettingUIDetailView(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ExtensionWidgetPool(*this)
{
}


// Initialization

void USettingUIDetailView::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!IsDesignTime())
	{
		FillSettingDetails(nullptr);
	}
}

void USettingUIDetailView::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	ExtensionWidgetPool.ReleaseAllSlateResources();
}


// Detail View

void USettingUIDetailView::FillSettingDetails(USettingUITypeResolver* InSetting)
{
	if (CurrentSetting != InSetting)
	{
		CurrentSetting = InSetting;

		UpdateTexts();
		UpdateExtensions();
	}
}

void USettingUIDetailView::UpdateTexts()
{
	if (Text_SettingName)
	{
		Text_SettingName->SetText(CurrentSetting.IsValid() ? CurrentSetting->GetDisplayName() : FText::GetEmpty());
	}

	if (RichText_Description)
	{
		RichText_Description->SetText(CurrentSetting.IsValid() ? CurrentSetting->GetDescription() : FText::GetEmpty());
	}

	if (RichText_DisabledDetails)
	{
		TArray<FText> DisabledDetailLines;

		if (CurrentSetting.IsValid() && CurrentSetting->GetEditableState().IsDisabled())
		{
			RichText_DisabledDetails->SetText(FText::Join(FText::FromString(TEXT("\n")), CurrentSetting->GetEditableState().DisabledReasons));
			RichText_DisabledDetails->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
		else
		{
			RichText_DisabledDetails->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void USettingUIDetailView::UpdateExtensions()
{
	if (Box_DetailsExtension)
	{
		// First release the widgets back into the pool.

		for (auto* ChildExtension : Box_DetailsExtension->GetAllChildren())
		{
			ExtensionWidgetPool.Release(Cast<UUserWidget>(ChildExtension));
		}

		// Remove the widgets from their container.

		Box_DetailsExtension->ClearChildren();

		// Load and create widget

		if (CurrentSetting.IsValid() && VisualData)
		{
			const auto ExtensionSoftClasses{ VisualData->GatherDetailExtensions(CurrentSetting.Get()) };

			// If already loading some widget, cancel it

			if (StreamingHandle.IsValid())
			{
				StreamingHandle->CancelHandle();
			}

			// Check should load widgets

			auto bEverythingAlreadyLoaded{ true };

			TArray<FSoftObjectPath> ExtensionPaths;
			ExtensionPaths.Reserve(ExtensionSoftClasses.Num());
			for (const auto& SoftClass : ExtensionSoftClasses)
			{
				bEverythingAlreadyLoaded &= SoftClass.IsValid();
				ExtensionPaths.Add(SoftClass.ToSoftObjectPath());
			}

			// Create widget immediately if already loaded

			if (bEverythingAlreadyLoaded)
			{
				for (const auto& SoftClass : ExtensionSoftClasses)
				{
					CreateDetailsExtension(CurrentSetting.Get(), SoftClass.Get());
				}

				ExtensionWidgetPool.ReleaseInactiveSlateResources();
			}

			// Load widgets

			else
			{
				StreamingHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(MoveTemp(ExtensionPaths), FStreamableDelegate::CreateWeakLambda(this, 
					[this, ExtensionSoftClasses] 
					{
						for (const auto& SoftClass : ExtensionSoftClasses)
						{
							CreateDetailsExtension(CurrentSetting.Get(), SoftClass.Get());
						}

						ExtensionWidgetPool.ReleaseInactiveSlateResources();
					}
				));
			}
		}
	}
}

void USettingUIDetailView::CreateDetailsExtension(USettingUITypeResolver* InSetting, TSubclassOf<USettingUIDetailExtension> ExtensionClass)
{
	if (InSetting && ExtensionClass)
	{
		if (auto* Extension{ ExtensionWidgetPool.GetOrCreateInstance(ExtensionClass) })
		{
			Extension->SetSetting(InSetting);

			auto* ExtensionSlot{ Box_DetailsExtension->AddChildToVerticalBox(Extension) };
			ExtensionSlot->SetHorizontalAlignment(ExtensionsHorizontalAlignment);
			ExtensionSlot->SetVerticalAlignment(ExtensionsVerticalAlignment);
		}
	}
}
