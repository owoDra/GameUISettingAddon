// Copyright (C) 2024 owoDra

#pragma once

#include "Components/ListView.h"

#include "SettingUIListView.generated.h"

class USettingUIListVisualData;
class STableViewBase;


/**
 * List view class of game settings
 */
UCLASS(meta = (EntryClass = SettingUIListEntry))
class GAUISETTING_API USettingUIListView : public UListView
{
	GENERATED_BODY()
public:
	USettingUIListView(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/////////////////////////////////////////////////////////////
	// Validation
public:
#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& InCompileLog) const override;
#endif

	/////////////////////////////////////////////////////////////
	// List View
protected:
	UPROPERTY(EditAnywhere, Category = "List View")
	TObjectPtr<const USettingUIListVisualData> VisualData;

protected:
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;
	virtual bool OnIsSelectableOrNavigableInternal(UObject* SelectedItem) override;

};
