// Copyright (C) 2024 owoDra

#pragma once

#include "Blueprint/UserWidgetPool.h"

#include "SettingUIDetailView.generated.h"

class USettingUITypeResolver;
class USettingUIDetailExtension;
class USettingUIDetailVisualData;
class UVerticalBox;
class UCommonRichTextBlock;
class UCommonTextBlock;
struct FStreamableHandle;


/**
 * Widget class to display details of setting option
 */
UCLASS(Abstract, meta = (DisableNativeTick))
class GAUISETTING_API USettingUIDetailView : public UUserWidget
{
	GENERATED_BODY()
public:
	USettingUIDetailView(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	///////////////////////////////////////////////////////////
	// Initialization
protected:
	virtual void NativeOnInitialized() override;

public:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;


	///////////////////////////////////////////////////////////
	// Detail View
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Detail View")
	TObjectPtr<const USettingUIDetailVisualData> VisualData;

	UPROPERTY(EditDefaultsOnly, Category = "Detail View")
	TEnumAsByte<EHorizontalAlignment> ExtensionsHorizontalAlignment{ EHorizontalAlignment::HAlign_Fill };

	UPROPERTY(EditDefaultsOnly, Category = "Detail View")
	TEnumAsByte<EVerticalAlignment> ExtensionsVerticalAlignment{ EVerticalAlignment::VAlign_Top };

protected:
	UPROPERTY(Transient)
	FUserWidgetPool ExtensionWidgetPool;

	UPROPERTY(Transient)
	TWeakObjectPtr<USettingUITypeResolver> CurrentSetting;

	TSharedPtr<FStreamableHandle> StreamingHandle;

public:
	UFUNCTION(BlueprintCallable, Category = "Detail View")
	void FillSettingDetails(USettingUITypeResolver* InSetting);

protected:
	virtual void UpdateTexts();
	virtual void UpdateExtensions();

	void CreateDetailsExtension(USettingUITypeResolver* InSetting, TSubclassOf<USettingUIDetailExtension> ExtensionClass);


	///////////////////////////////////////////////////////////
	// Bound Widgets
private:	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonTextBlock> Text_SettingName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonRichTextBlock> RichText_Description;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonRichTextBlock> RichText_DisabledDetails;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UVerticalBox> Box_DetailsExtension;

};
