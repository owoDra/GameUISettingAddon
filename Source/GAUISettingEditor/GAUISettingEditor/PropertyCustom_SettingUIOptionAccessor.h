// Copyright (C) 2023 owoDra

#pragma once

#include "IPropertyTypeCustomization.h"

class UObject;
class STextBlock;
class SSearchableComboBox;


/**
 * Property customization classes to help edit SettingUIOption data in the Editor
 */
class FPropertyCustom_SettingUIOptionAccessor : public IPropertyTypeCustomization
{
private:
	typedef FPropertyCustom_SettingUIOptionAccessor ThisClass;

	//////////////////////////////////////////////////////////////////////
	// Property Data
protected:
	static const FName NAME_Property_SettingUIOptionAccessor;
	static const FName NAME_Property_SettingUIOptionAccessor_Type;
	static const FName NAME_Property_SettingUIOptionAccessor_Source;
	static const FName NAME_Property_SettingUIOptionAccessor_GetterName;
	static const FName NAME_Property_SettingUIOptionAccessor_SetterName;
	static const FName NAME_Property_SettingUIOptionAccessor_OptionGetterName;

protected:
	//
	// Handle to the "SettingUIOptionAccessor" data itself to be edited
	//
	TSharedPtr<IPropertyHandle> PropertyHandle_SettingUIOption{ nullptr };

	//
	// Handle to the "Type" property in the SettingUIOptionAccessor data to be edited
	//
	TSharedPtr<IPropertyHandle> PropertyHandle_Type{ nullptr };

	//
	// Handle to the "Source" property in the SettingUIOptionAccessor data to be edited
	//
	TSharedPtr<IPropertyHandle> PropertyHandle_Source{ nullptr };

	//
	// Handle to the "GetterName" property in the SettingUIOptionAccessor data to be edited
	//
	TSharedPtr<IPropertyHandle> PropertyHandle_GetterName{ nullptr };

	//
	// Handle to the "SetterName" property in the SettingUIOptionAccessor data to be edited
	//
	TSharedPtr<IPropertyHandle> PropertyHandle_SetterName{ nullptr };

	//
	// Handle to the "OptionGetterName" property in the SettingUIOptionAccessor data to be edited
	//
	TSharedPtr<IPropertyHandle> PropertyHandle_OptionGetterName{ nullptr };


	//////////////////////////////////////////////////////////////////////
	// Register Module
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();
	static void RegisterToPropertyEditorModule(FPropertyEditorModule& PropertyModule);
	static void UnregisterToPropertyEditorModule(FPropertyEditorModule& PropertyModule);


	//////////////////////////////////////////////////////////////////////
	// Customization
public:
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

protected:
	virtual void CustomizeProperty_Type(IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);
	virtual void CustomizeProperty_Source(IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);
	virtual void CustomizeProperty_GetterName(IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);
	virtual void CustomizeProperty_SetterName(IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);
	virtual void CustomizeProperty_OptionGetterName(IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);

	virtual void HandlePropertyChange();


	//////////////////////////////////////////////////////////////////////
	// Selected Key
protected:
	//
	// Value of the previously selected "Type"
	//
	FString PrevSelectedTypeName{ FString() };

	//
	// Value of the previously selected "Source"
	//
	FString PrevSelectedSourceName{ FString() };

	//
	// UFunction to filter function name candidates
	//
	TWeakObjectPtr<UFunction> GetterTemplateFunction{ nullptr };
	TWeakObjectPtr<UFunction> SetterTemplateFunction{ nullptr };
	TWeakObjectPtr<UFunction> OptionGetterTemplateFunction{ nullptr };

protected:
	/**
	 * Review and update key property changes that affect other value selections
	 */
	bool RefreshSelectedKey();

	/**
	 * Update TemplateFunctions
	 */
	virtual void UpdateTemplateFunction(const UClass* ResolverClass);

	/**
	 * Get the class currently selected in ResolverTypeClass
	 */
	virtual const UClass* GetPropertyValueAsClass(const TSharedPtr<IPropertyHandle>& Handle) const;


	//////////////////////////////////////////////////////////////////////
	// SuggestList
protected:
	//
	// Slate widget to display the currently selected function
	//
	TWeakPtr<STextBlock> RowTextWidget_GetterName{ nullptr };
	TWeakPtr<STextBlock> RowTextWidget_SetterName{ nullptr };
	TWeakPtr<STextBlock> RowTextWidget_OptionGetterName{ nullptr };

	//
	// Slate widget to display selectable functions
	//
	TWeakPtr<SSearchableComboBox> SuggestListWidget_GetterName{ nullptr };
	TWeakPtr<SSearchableComboBox> SuggestListWidget_SetterName{ nullptr };
	TWeakPtr<SSearchableComboBox> SuggestListWidget_OptionGetterName{ nullptr };

	//
	// Option list in CombBox
	//
	TArray<TSharedPtr<FString>> SuggestListOptions_GetterName;
	TArray<TSharedPtr<FString>> SuggestListOptions_SetterName;
	TArray<TSharedPtr<FString>> SuggestListOptions_OptionGetterName;

	//
	// Option name if class is not selected
	//
	TSharedPtr<FString> NoneStringOption{ nullptr };

protected:
	/**
	 * Add an empty entry to the CombBox once and deselect User
	 */
	void InitSuggestList_GetterName();
	void InitSuggestList_SetterName();
	void InitSuggestList_OptionGetterName();
	void InitNoneStringOption();

	/**
	 * Delete everything in CombBox to None only
	 */
	void ResetSuggestList_GetterName();
	void ResetSuggestList_SetterName();
	void ResetSuggestList_OptionGetterName();
	void ResetSuggestList(TArray<TSharedPtr<FString>>& List);

	/**
	 * Called when there is a change in a variable.
	 * Filter function name candidates based on the current state and update the SuggestListOptions value.
	 */
	void RefreshSuggestList_GetterName();
	void RefreshSuggestList_SetterName();
	void RefreshSuggestList_OptionGetterName();
	void RefreshSuggestList(
		TSharedPtr<IPropertyHandle>& Handle
		, TArray<TSharedPtr<FString>>& Options
		, TWeakPtr<SSearchableComboBox>& List
		, TWeakPtr<STextBlock>& Text
		, const UFunction* Template);

	/**
	 * Disable the call candidate list when SourceClass has an invalid reference
	 */
	void InvalidateSuggestList_GetterName();
	void InvalidateSuggestList_SetterName();
	void InvalidateSuggestList_OptionGetterName();
	void InvalidateSuggestList();

	/**
	 * Called when a candidate function name is selected from the CombBox
	 * Updates the current FunctionName value.
	 */
	void OnSuggestSelected_GetterName(TSharedPtr<FString> SelectedStringPtr, ESelectInfo::Type SelectInfo);
	void OnSuggestSelected_SetterName(TSharedPtr<FString> SelectedStringPtr, ESelectInfo::Type SelectInfo);
	void OnSuggestSelected_OptionGetterName(TSharedPtr<FString> SelectedStringPtr, ESelectInfo::Type SelectInfo);

	/**
	 * Set the name of the function under selection
	 */
	void SetFunctionNameValue(TSharedPtr<IPropertyHandle>& Handle, TWeakPtr<STextBlock>& Widget, FName Value);

	/**
	 * Returns whether the given function matches the signature specified in TemplateFunction
	 */
	virtual bool IsSignatureCompatible(const UFunction* TestFunction, const UFunction* TemplateFunction) const;

};
