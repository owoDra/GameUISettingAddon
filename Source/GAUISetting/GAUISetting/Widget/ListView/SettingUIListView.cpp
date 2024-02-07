// Copyright (C) 2024 owoDra

#include "SettingUIListView.h"

#include "Resolver/SettingUITypeResolver.h"
#include "Entry/SettingUIListEntry.h"
#include "SettingUIListVisualData.h"

#include "GUIExtLogs.h"

#if WITH_EDITOR
#include "Editor/WidgetCompilerLog.h"
#endif

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUIListView)

////////////////////////////////////////////////////////////////////

USettingUIListView::USettingUIListView(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


// Validation

#if WITH_EDITOR
void USettingUIListView::ValidateCompiledDefaults(IWidgetCompilerLog& InCompileLog) const
{
	Super::ValidateCompiledDefaults(InCompileLog);

	if (!VisualData)
	{
		InCompileLog.Error(FText::Format(FText::FromString("{0} has no VisualData defined."), FText::FromString(GetName())));
	}
}
#endif


// List View

UUserWidget& USettingUIListView::OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable)
{
	auto* SettingItem{ Cast<USettingUITypeResolver>(Item) };
	auto SettingEntryClass{ TSubclassOf<USettingUIListEntry>(DesiredEntryClass) };

	// Find Entry class from visual data

	if (VisualData)
	{
		if (const auto EntryClassSetting{ VisualData->GetEntryForSetting(SettingItem) })
		{
			SettingEntryClass = EntryClassSetting;
		}
		else
		{
			// UE_LOG(LogGameExt_UI, Error, TEXT("USettingUIListView: No Entry Class Found!"));
		}
	}
	else
	{
		// UE_LOG(LogGameExt_UI, Error, TEXT("USettingUIListView: No VisualData Defined!"));
	}

	// Create entry

	auto& EntryWidget = GenerateTypedEntry<USettingUIListEntry>(SettingEntryClass, OwnerTable);

	if (!IsDesignTime())
	{
		EntryWidget.SetSetting(SettingItem);
	}

	return EntryWidget;
}

bool USettingUIListView::OnIsSelectableOrNavigableInternal(UObject* SelectedItem)
{
	auto* Setting{ Cast<USettingUITypeResolver>(SelectedItem) };
	return Setting ? Setting->IsSelectable() : false;
}
