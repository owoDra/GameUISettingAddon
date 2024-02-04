// Copyright (C) 2024 owoDra

#include "AssetTypeActions_SettingUITable.h"

#include "Type/SettingUITable.h"

#include "DataTableEditorModule.h"
#include "Misc/MessageDialog.h"


#define LOCTEXT_NAMESPACE "AssetTypeActions"

FText FAssetTypeActions_SettingUITable::GetName() const
{
	return LOCTEXT("SettingUITable", "Setting UI Options Table");
}

FColor FAssetTypeActions_SettingUITable::GetTypeColor() const
{
	return FColor(153, 102, 102);
}

UClass* FAssetTypeActions_SettingUITable::GetSupportedClass() const
{
	return USettingUITable::StaticClass();
}

const TArray<FText>& FAssetTypeActions_SettingUITable::GetSubMenus() const
{
	static const TArray<FText> SubMenus
	{
		LOCTEXT("SettingUISubMenu", "Setting UI")
	};

	return SubMenus;
}


void FAssetTypeActions_SettingUITable::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	TArray<UDataTable*> DataTablesToOpen;
	TArray<UDataTable*> InvalidDataTables;

	for (auto* Obj : InObjects)
	{
		if (auto* Table{ Cast<UDataTable>(Obj) })
		{
			if (Table->GetRowStruct())
			{
				DataTablesToOpen.Add(Table);
			}
			else
			{
				InvalidDataTables.Add(Table);
			}
		}
	}

	if (InvalidDataTables.Num() > 0)
	{
		FTextBuilder DataTablesListText;
		DataTablesListText.Indent();
		for (auto* Table : InvalidDataTables)
		{
			const auto ResolvedRowStructName{ Table->GetRowStructPathName() };
			DataTablesListText.AppendLineFormat(LOCTEXT("DataTable_MissingRowStructListEntry", "* {0} (Row Structure: {1})"), FText::FromString(Table->GetName()), FText::FromString(ResolvedRowStructName.ToString()));
		}

		const EAppReturnType::Type DlgResult = FMessageDialog::Open(
			EAppMsgType::YesNoCancel,
			FText::Format(LOCTEXT("DataTable_MissingRowStructMsg", "The following Data Tables are missing their row structure and will not be editable.\n\n{0}\n\nDo you want to open these data tables?"), DataTablesListText.ToText()),
			LOCTEXT("DataTable_MissingRowStructTitle", "Continue?")
		);

		switch (DlgResult)
		{
		case EAppReturnType::Yes:
			DataTablesToOpen.Append(InvalidDataTables);
			break;
		case EAppReturnType::Cancel:
			return;
		default:
			break;
		}
	}

	FDataTableEditorModule& DataTableEditorModule = FModuleManager::LoadModuleChecked<FDataTableEditorModule>("DataTableEditor");
	for (auto* Table : DataTablesToOpen)
	{
		DataTableEditorModule.CreateDataTableEditor(EToolkitMode::Standalone, EditWithinLevelEditor, Table);
	}
}

#undef LOCTEXT_NAMESPACE
