// Copyright (C) 2023 owoDra

#include "PropertyCustom_SettingUIOptionAccessor.h"

#include "Type/SettingUIOptionTypes.h"
#include "Resolver/SettingUITypeResolver.h"

#include "GSCSubsystem.h"
#include "GSCGameUserSettings.h"

#include "GameFramework/GameUserSettings.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "SSearchableComboBox.h"

///////////////////////////////////////////////////////

// Property Data

const FName FPropertyCustom_SettingUIOptionAccessor::NAME_Property_SettingUIOptionAccessor{ FSettingUIOptionAccessor::StaticStruct()->GetFName() };
const FName FPropertyCustom_SettingUIOptionAccessor::NAME_Property_SettingUIOptionAccessor_Type{ GET_MEMBER_NAME_CHECKED(FSettingUIOptionAccessor, Type) };
const FName FPropertyCustom_SettingUIOptionAccessor::NAME_Property_SettingUIOptionAccessor_Source{ GET_MEMBER_NAME_CHECKED(FSettingUIOptionAccessor, Source) };
const FName FPropertyCustom_SettingUIOptionAccessor::NAME_Property_SettingUIOptionAccessor_GetterName{ GET_MEMBER_NAME_CHECKED(FSettingUIOptionAccessor, GetterName) };
const FName FPropertyCustom_SettingUIOptionAccessor::NAME_Property_SettingUIOptionAccessor_SetterName{ GET_MEMBER_NAME_CHECKED(FSettingUIOptionAccessor, SetterName) };
const FName FPropertyCustom_SettingUIOptionAccessor::NAME_Property_SettingUIOptionAccessor_OptionGetterName{ GET_MEMBER_NAME_CHECKED(FSettingUIOptionAccessor, OptionGetterName) };


// Register Module

TSharedRef<IPropertyTypeCustomization> FPropertyCustom_SettingUIOptionAccessor::MakeInstance()
{
	return MakeShareable(new FPropertyCustom_SettingUIOptionAccessor());
}

void FPropertyCustom_SettingUIOptionAccessor::RegisterToPropertyEditorModule(FPropertyEditorModule& PropertyModule)
{
	PropertyModule.RegisterCustomPropertyTypeLayout(
		FPropertyCustom_SettingUIOptionAccessor::NAME_Property_SettingUIOptionAccessor,
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FPropertyCustom_SettingUIOptionAccessor::MakeInstance));
}

void FPropertyCustom_SettingUIOptionAccessor::UnregisterToPropertyEditorModule(FPropertyEditorModule& PropertyModule)
{
	PropertyModule.UnregisterCustomPropertyTypeLayout(FPropertyCustom_SettingUIOptionAccessor::NAME_Property_SettingUIOptionAccessor);
}


// Customization

void FPropertyCustom_SettingUIOptionAccessor::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	HeaderRow
		.NameContent()
		[
			PropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		[
			PropertyHandle->CreatePropertyValueWidget()
		];
}

void FPropertyCustom_SettingUIOptionAccessor::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	InitNoneStringOption();

	// Set callbacks for variable changes

	PropertyHandle_SettingUIOption = PropertyHandle;
	auto HandlePropertyChangeDelegate{ FSimpleDelegate::CreateSP(this, &ThisClass::HandlePropertyChange) };
	PropertyHandle->SetOnPropertyValueChanged(HandlePropertyChangeDelegate);
	PropertyHandle->SetOnChildPropertyValueChanged(HandlePropertyChangeDelegate);

	// Added section on Variable "Type"

	PropertyHandle_Type = PropertyHandle->GetChildHandle(FPropertyCustom_SettingUIOptionAccessor::NAME_Property_SettingUIOptionAccessor_Type);
	if (PropertyHandle_Type.IsValid())
	{
		CustomizeProperty_Type(ChildBuilder, CustomizationUtils);
	}

	// Added section on Variable "Source"

	PropertyHandle_Source = PropertyHandle->GetChildHandle(FPropertyCustom_SettingUIOptionAccessor::NAME_Property_SettingUIOptionAccessor_Source);
	if (PropertyHandle_Source.IsValid())
	{
		CustomizeProperty_Source(ChildBuilder, CustomizationUtils);
	}

	RefreshSelectedKey();

	// Added section on Variable "GetterName"
	
	PropertyHandle_GetterName = PropertyHandle->GetChildHandle(FPropertyCustom_SettingUIOptionAccessor::NAME_Property_SettingUIOptionAccessor_GetterName);
	if (PropertyHandle_GetterName.IsValid())
	{
		CustomizeProperty_GetterName(ChildBuilder, CustomizationUtils);
	}

	// Added section on Variable "SetterName"

	PropertyHandle_SetterName = PropertyHandle->GetChildHandle(FPropertyCustom_SettingUIOptionAccessor::NAME_Property_SettingUIOptionAccessor_SetterName);
	if (PropertyHandle_SetterName.IsValid())
	{
		CustomizeProperty_SetterName(ChildBuilder, CustomizationUtils);
	}

	// Added section on Variable "OptionGetterName"

	PropertyHandle_OptionGetterName = PropertyHandle->GetChildHandle(FPropertyCustom_SettingUIOptionAccessor::NAME_Property_SettingUIOptionAccessor_OptionGetterName);
	if (PropertyHandle_OptionGetterName.IsValid())
	{
		CustomizeProperty_OptionGetterName(ChildBuilder, CustomizationUtils);
	}
}

void FPropertyCustom_SettingUIOptionAccessor::CustomizeProperty_Type(IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	ChildBuilder
		.AddProperty(PropertyHandle_Type.ToSharedRef())
		.ShouldAutoExpand(true)
		.IsEnabled(true)
		.Visibility(EVisibility::Visible);
}

void FPropertyCustom_SettingUIOptionAccessor::CustomizeProperty_Source(IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	ChildBuilder
		.AddProperty(PropertyHandle_Source.ToSharedRef())
		.ShouldAutoExpand(true)
		.IsEnabled(true)
		.Visibility(EVisibility::Visible);
}

void FPropertyCustom_SettingUIOptionAccessor::CustomizeProperty_GetterName(IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	//  Initialize CombBox data

	InitSuggestList_GetterName();

	RefreshSuggestList_GetterName();

	// Build a widget about the name of the function being selected

	FText TextRowText;
	PropertyHandle_GetterName->GetValueAsDisplayText(TextRowText);

	const auto TextRowWidgetRef
	{
		SNew(STextBlock)
			.Text(TextRowText)
	};

	RowTextWidget_GetterName = TextRowWidgetRef;

	// Build a widget about the suggest list

	const auto SearchableComboBoxRef
	{
		SNew(SSearchableComboBox)
			.OptionsSource(&SuggestListOptions_GetterName)
			.OnGenerateWidget_Lambda(
				[](const TSharedPtr<FString> InItem) -> TSharedRef<SWidget>
				{
					return SNew(STextBlock).Text(FText::FromString(*InItem));
				}
			)
			.OnSelectionChanged(this, &ThisClass::OnSuggestSelected_GetterName)
			.ContentPadding(2.f)
			.MaxListHeight(200.f)
			.IsEnabled(true)
			.Content()
			[
				TextRowWidgetRef
			]
	};

	SuggestListWidget_GetterName = SearchableComboBoxRef;

	// Build a widget about where to edit the function name

	ChildBuilder
		.AddCustomRow(PropertyHandle_GetterName->GetPropertyDisplayName())
		.Visibility(EVisibility::Visible)
		.NameContent()
		[
			SNew(STextBlock)
				.Text(PropertyHandle_GetterName->GetPropertyDisplayName())
				.Font(IDetailLayoutBuilder::GetDetailFont())
		]
		.ValueContent()
		[
			SNew(SVerticalBox) + SVerticalBox::Slot()
									.AutoHeight()
									.VAlign(VAlign_Fill)
									.Padding(0.f)
									[
										SearchableComboBoxRef
									]
		];
}

void FPropertyCustom_SettingUIOptionAccessor::CustomizeProperty_SetterName(IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	//  Initialize CombBox data

	InitSuggestList_SetterName();

	RefreshSuggestList_SetterName();

	// Build a widget about the name of the function being selected

	FText TextRowText;
	PropertyHandle_SetterName->GetValueAsDisplayText(TextRowText);

	const auto TextRowWidgetRef
	{
		SNew(STextBlock)
			.Text(TextRowText)
	};

	RowTextWidget_SetterName = TextRowWidgetRef;

	// Build a widget about the suggest list

	const auto SearchableComboBoxRef
	{
		SNew(SSearchableComboBox)
			.OptionsSource(&SuggestListOptions_SetterName)
			.OnGenerateWidget_Lambda(
				[](const TSharedPtr<FString> InItem) -> TSharedRef<SWidget>
				{
					return SNew(STextBlock).Text(FText::FromString(*InItem));
				}
			)
			.OnSelectionChanged(this, &ThisClass::OnSuggestSelected_SetterName)
			.ContentPadding(2.f)
			.MaxListHeight(200.f)
			.IsEnabled(true)
			.Content()
			[
				TextRowWidgetRef
			]
	};

	SuggestListWidget_SetterName = SearchableComboBoxRef;

	// Build a widget about where to edit the function name

	ChildBuilder
		.AddCustomRow(PropertyHandle_SetterName->GetPropertyDisplayName())
		.Visibility(EVisibility::Visible)
		.NameContent()
		[
			SNew(STextBlock)
				.Text(PropertyHandle_SetterName->GetPropertyDisplayName())
				.Font(IDetailLayoutBuilder::GetDetailFont())
		]
		.ValueContent()
		[
			SNew(SVerticalBox) + SVerticalBox::Slot()
				.AutoHeight()
				.VAlign(VAlign_Fill)
				.Padding(0.f)
				[
					SearchableComboBoxRef
				]
		];
}

void FPropertyCustom_SettingUIOptionAccessor::CustomizeProperty_OptionGetterName(IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	//  Initialize CombBox data

	InitSuggestList_OptionGetterName();

	RefreshSuggestList_OptionGetterName();

	// Build a widget about the name of the function being selected

	FText TextRowText;
	PropertyHandle_OptionGetterName->GetValueAsDisplayText(TextRowText);

	const auto TextRowWidgetRef
	{
		SNew(STextBlock)
			.Text(TextRowText)
	};

	RowTextWidget_OptionGetterName = TextRowWidgetRef;

	// Build a widget about the suggest list

	const auto SearchableComboBoxRef
	{
		SNew(SSearchableComboBox)
			.OptionsSource(&SuggestListOptions_OptionGetterName)
			.OnGenerateWidget_Lambda(
				[](const TSharedPtr<FString> InItem) -> TSharedRef<SWidget>
				{
					return SNew(STextBlock).Text(FText::FromString(*InItem));
				}
			)
			.OnSelectionChanged(this, &ThisClass::OnSuggestSelected_OptionGetterName)
			.ContentPadding(2.f)
			.MaxListHeight(200.f)
			.IsEnabled(true)
			.Content()
			[
				TextRowWidgetRef
			]
	};

	SuggestListWidget_OptionGetterName = SearchableComboBoxRef;

	// Build a widget about where to edit the function name

	ChildBuilder
		.AddCustomRow(PropertyHandle_OptionGetterName->GetPropertyDisplayName())
		.Visibility(EVisibility::Visible)
		.NameContent()
		[
			SNew(STextBlock)
				.Text(PropertyHandle_OptionGetterName->GetPropertyDisplayName())
				.Font(IDetailLayoutBuilder::GetDetailFont())
		]
		.ValueContent()
		[
			SNew(SVerticalBox) + SVerticalBox::Slot()
				.AutoHeight()
				.VAlign(VAlign_Fill)
				.Padding(0.f)
				[
					SearchableComboBoxRef
				]
		];
}


void FPropertyCustom_SettingUIOptionAccessor::HandlePropertyChange()
{
	if (RefreshSelectedKey())
	{
		RefreshSuggestList_GetterName();
		RefreshSuggestList_SetterName();
		RefreshSuggestList_OptionGetterName();
	}
}


// Selected Key

bool FPropertyCustom_SettingUIOptionAccessor::RefreshSelectedKey()
{
	// If the property handle is invalid, returns false and invalidates the list.

	if (!PropertyHandle_Source.IsValid() || !PropertyHandle_Type.IsValid())
	{
		InvalidateSuggestList();
		return false;
	}

	// If "Type" is not selected, returns false and invalidates the list

	FString SelectedTypeName;
	PropertyHandle_Type->GetValueAsDisplayString(SelectedTypeName);
	if (SelectedTypeName.IsEmpty())
	{
		InvalidateSuggestList();
		return false;
	}

	// If "Source" is not selected, returns false and invalidates the list

	FString SelectedSourceName;
	PropertyHandle_Source->GetValueAsDisplayString(SelectedSourceName);
	if (SelectedSourceName.IsEmpty())
	{
		InvalidateSuggestList();
		return false;
	}

	// Skip update if item is unchanged

	const auto bHasTypeChanged{ SelectedTypeName != PrevSelectedTypeName };
	const auto bHasSourceChanged{ SelectedSourceName != PrevSelectedSourceName };

	PrevSelectedTypeName = SelectedTypeName;
	PrevSelectedSourceName = SelectedSourceName;

	if (!bHasTypeChanged && !bHasSourceChanged)
	{
		return false;
	}

	// Disable the selected type if it was invalid.

	const auto* SelectedTypeClass{ GetPropertyValueAsClass(PropertyHandle_Type) };
	if (!SelectedTypeClass)
	{
		InvalidateSuggestList();
		return false;
	}

	// Disable the selected source if it was invalid.

	const auto* SelectedSourceClass{ GetPropertyValueAsClass(PropertyHandle_Source) };
	if (!SelectedSourceClass)
	{
		InvalidateSuggestList();
		return false;
	}

	// Update template

	UpdateTemplateFunction(SelectedTypeClass);

	return true;
}

void FPropertyCustom_SettingUIOptionAccessor::UpdateTemplateFunction(const UClass* ResolverClass)
{
	if (ResolverClass)
	{
		GetterTemplateFunction = USettingUITypeResolver::GetGetterTemplate(ResolverClass);
		SetterTemplateFunction = USettingUITypeResolver::GetSetterTemplate(ResolverClass);
		OptionGetterTemplateFunction = USettingUITypeResolver::GetOptionGetterTemplate(ResolverClass);
	}
}

const UClass* FPropertyCustom_SettingUIOptionAccessor::GetPropertyValueAsClass(const TSharedPtr<IPropertyHandle>& Handle) const
{
	void* ValueData;
	Handle->GetValueData(ValueData);

	if (ValueData)
	{
		if (auto** ClassData{ static_cast<UClass**>(ValueData) })
		{
			auto* Class{ *ClassData ? *ClassData : UGSCGameUserSettings::StaticClass()};

			return Class;
		}
	}

	return nullptr;
}


// SuggestList

void FPropertyCustom_SettingUIOptionAccessor::InitSuggestList_GetterName()
{
	if (ensure(NoneStringOption.IsValid()))
	{
		SuggestListOptions_GetterName.EmplaceAt(0, NoneStringOption);
	}
}

void FPropertyCustom_SettingUIOptionAccessor::InitSuggestList_SetterName()
{
	if (ensure(NoneStringOption.IsValid()))
	{
		SuggestListOptions_SetterName.EmplaceAt(0, NoneStringOption);
	}
}

void FPropertyCustom_SettingUIOptionAccessor::InitSuggestList_OptionGetterName()
{
	if (ensure(NoneStringOption.IsValid()))
	{
		SuggestListOptions_OptionGetterName.EmplaceAt(0, NoneStringOption);
	}
}

void FPropertyCustom_SettingUIOptionAccessor::InitNoneStringOption()
{
	if (!NoneStringOption.IsValid())
	{
		NoneStringOption = MakeShareable(new FString(FName(NAME_None).ToString()));
	}
}


void FPropertyCustom_SettingUIOptionAccessor::ResetSuggestList_GetterName()
{
	ResetSuggestList(SuggestListOptions_GetterName);
}

void FPropertyCustom_SettingUIOptionAccessor::ResetSuggestList_SetterName()
{
	ResetSuggestList(SuggestListOptions_SetterName);
}

void FPropertyCustom_SettingUIOptionAccessor::ResetSuggestList_OptionGetterName()
{
	ResetSuggestList(SuggestListOptions_OptionGetterName);
}

void FPropertyCustom_SettingUIOptionAccessor::ResetSuggestList(TArray<TSharedPtr<FString>>& List)
{
	for (auto It{ List.CreateIterator() }; It; ++It)
	{
		auto& StringPtrIt{ *It };
		if (StringPtrIt != NoneStringOption)
		{
			StringPtrIt.Reset();
			It.RemoveCurrent();
		}
	}
}


void FPropertyCustom_SettingUIOptionAccessor::RefreshSuggestList_GetterName()
{
	if (PropertyHandle_GetterName.IsValid() && PropertyHandle_Type.IsValid() && PropertyHandle_Source.IsValid())
	{
		ResetSuggestList_GetterName();
		RefreshSuggestList(
			PropertyHandle_GetterName
			, SuggestListOptions_GetterName
			, SuggestListWidget_GetterName
			, RowTextWidget_GetterName
			, GetterTemplateFunction.Get());
	}
	else
	{
		InvalidateSuggestList_GetterName();
	}
}

void FPropertyCustom_SettingUIOptionAccessor::RefreshSuggestList_SetterName()
{
	if (PropertyHandle_SetterName.IsValid() && PropertyHandle_Type.IsValid() && PropertyHandle_Source.IsValid())
	{
		ResetSuggestList_SetterName();
		RefreshSuggestList(
			PropertyHandle_SetterName
			, SuggestListOptions_SetterName
			, SuggestListWidget_SetterName
			, RowTextWidget_SetterName
			, SetterTemplateFunction.Get());
	}
	else
	{
		InvalidateSuggestList_SetterName();
	}
}

void FPropertyCustom_SettingUIOptionAccessor::RefreshSuggestList_OptionGetterName()
{
	if (PropertyHandle_OptionGetterName.IsValid() && PropertyHandle_Type.IsValid() && PropertyHandle_Source.IsValid())
	{
		ResetSuggestList_OptionGetterName();
		RefreshSuggestList(
			PropertyHandle_OptionGetterName
			, SuggestListOptions_OptionGetterName
			, SuggestListWidget_OptionGetterName
			, RowTextWidget_OptionGetterName
			, OptionGetterTemplateFunction.Get());
	}
	else
	{
		InvalidateSuggestList_OptionGetterName();
	}
}

void FPropertyCustom_SettingUIOptionAccessor::RefreshSuggestList(
	TSharedPtr<IPropertyHandle>& Handle
	, TArray<TSharedPtr<FString>>& Options
	, TWeakPtr<SSearchableComboBox>& List
	, TWeakPtr<STextBlock>& Text
	, const UFunction* Template)
{
	FName SelectedFunctionName{ NAME_None };
	Handle->GetValue(SelectedFunctionName);

	TArray<FName> FoundList;
	auto bFoundSpecifiedFunction{ false };
	for (TFieldIterator<UFunction> It{ GetPropertyValueAsClass(PropertyHandle_Source), EFieldIteratorFlags::IncludeSuper}; It; ++It)
	{
		const auto* FunctionIt{ *It };

		if (FunctionIt && Template && IsSignatureCompatible(FunctionIt, Template))
		{
			auto FunctionItName{ FunctionIt->GetFName() };
			if (FunctionItName == SelectedFunctionName)
			{
				bFoundSpecifiedFunction = true;
			}

			FoundList.AddUnique(MoveTemp(FunctionItName));
		}
	}

	// Set to None if there is no function name already selected

	if (!bFoundSpecifiedFunction)
	{
		SetFunctionNameValue(Handle, Text, NAME_None);
	}

	// Update suggest list

	for (const auto& Each : FoundList)
	{
		const auto StringName{ Each.ToString() };
		const auto bAlreadyContains
		{
			Options.ContainsByPredicate(
				[&StringName](const TSharedPtr<FString>& SuggestListOption)
				{
					return SuggestListOption && SuggestListOption->Equals(StringName);
				}
			)
		};

		if (bAlreadyContains)
		{
			continue;
		}

		Options.Emplace(MakeShareable(new FString(StringName)));
	}

	// Update CombBox

	if (const auto& SearchableComboBox{ List.Pin() })
	{
		SearchableComboBox->RefreshOptions();
	}
}


void FPropertyCustom_SettingUIOptionAccessor::InvalidateSuggestList_GetterName()
{
	ResetSuggestList_GetterName();

	SetFunctionNameValue(PropertyHandle_GetterName, RowTextWidget_GetterName, NAME_None);
}

void FPropertyCustom_SettingUIOptionAccessor::InvalidateSuggestList_SetterName()
{
	ResetSuggestList_SetterName();

	SetFunctionNameValue(PropertyHandle_SetterName, RowTextWidget_SetterName, NAME_None);
}

void FPropertyCustom_SettingUIOptionAccessor::InvalidateSuggestList_OptionGetterName()
{
	ResetSuggestList_OptionGetterName();

	SetFunctionNameValue(PropertyHandle_OptionGetterName, RowTextWidget_OptionGetterName, NAME_None);
}

void FPropertyCustom_SettingUIOptionAccessor::InvalidateSuggestList()
{
	InvalidateSuggestList_GetterName();
	InvalidateSuggestList_SetterName();
	InvalidateSuggestList_OptionGetterName();
}


void FPropertyCustom_SettingUIOptionAccessor::OnSuggestSelected_GetterName(TSharedPtr<FString> SelectedStringPtr, ESelectInfo::Type SelectInfo)
{
	if (const auto* SelectedString{ SelectedStringPtr.Get() })
	{
		SetFunctionNameValue(PropertyHandle_GetterName, RowTextWidget_GetterName, **SelectedString);
	}
}

void FPropertyCustom_SettingUIOptionAccessor::OnSuggestSelected_SetterName(TSharedPtr<FString> SelectedStringPtr, ESelectInfo::Type SelectInfo)
{
	if (const auto* SelectedString{ SelectedStringPtr.Get() })
	{
		SetFunctionNameValue(PropertyHandle_SetterName, RowTextWidget_SetterName, **SelectedString);
	}
}

void FPropertyCustom_SettingUIOptionAccessor::OnSuggestSelected_OptionGetterName(TSharedPtr<FString> SelectedStringPtr, ESelectInfo::Type SelectInfo)
{
	if (const auto* SelectedString{ SelectedStringPtr.Get() })
	{
		SetFunctionNameValue(PropertyHandle_OptionGetterName, RowTextWidget_OptionGetterName, **SelectedString);
	}
}


void FPropertyCustom_SettingUIOptionAccessor::SetFunctionNameValue(TSharedPtr<IPropertyHandle>& Handle, TWeakPtr<STextBlock>& Widget, FName Value)
{
	if (Handle.IsValid())
	{
		Handle->SetValue(Value);
	}

	if (const auto & TextWidget{ Widget.Pin() })
	{
		TextWidget->SetText(FText::FromName(Value));
	}
}

bool FPropertyCustom_SettingUIOptionAccessor::IsSignatureCompatible(const UFunction* TestFunction, const UFunction* TemplateFunction) const
{
	// Verify that the function to be verified and the function used for verification are valid

	if (!TestFunction || !TemplateFunction)
	{
		return false;
	}

	// Create lambda function to verify if properties are of the same type

	auto ArePropertiesTheSame
	{
		[](const FProperty* A, const FProperty* B)
		{
			if (A == B)
			{
				return true;
			}

			if (!A || !B)
			{
				return false;
			}

			if (A->GetSize() != B->GetSize())
			{
				return false;
			}

			if (A->GetOffset_ForGC() != B->GetOffset_ForGC())
			{
				return false;
			}

			if (!A->SameType(B))
			{
				if ((B->IsA(FEnumProperty::StaticClass()) && A->IsA(FByteProperty::StaticClass())) ||
					(A->IsA(FEnumProperty::StaticClass()) && B->IsA(FByteProperty::StaticClass())))
				{
					return true;
				}

				if (A->PropertyFlags & B->PropertyFlags & CPF_ReturnParm && A->IsA(B->GetClass()))
				{
					return true;
				}

				return false;
			}

			return true;
		}
	};

	// Verify that the signatures are equal by comparing the properties of both functions

	const uint64 IgnoreFlags{ CPF_ReturnParm | UFunction::GetDefaultIgnoredSignatureCompatibilityFlags() };

	TFieldIterator<FProperty> IteratorA{ TemplateFunction };
	TFieldIterator<FProperty> IteratorB{ TestFunction };

	while (IteratorA && (IteratorA->PropertyFlags & CPF_Parm))
	{
		if (IteratorB && (IteratorB->PropertyFlags & CPF_Parm))
		{
			const FProperty* PropA = *IteratorA;
			const FProperty* PropB = *IteratorB;

			const uint64 PropertyMash{ PropA->PropertyFlags ^ PropB->PropertyFlags };
			if (!ArePropertiesTheSame(PropA, PropB) || ((PropertyMash & ~IgnoreFlags) != 0))
			{
				return false;
			}
		}

		// Returns false if there is a mismatch in the number of properties in both functions

		else
		{
			return false;
		}

		++IteratorA;
		++IteratorB;
	}

	return true;
}
