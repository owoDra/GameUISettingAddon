// Copyright (C) 2024 owoDra

#include "AssetTypeActions_SettingUIDetailVisualData.h"

#include "Widget/DetailView/SettingUIDetailVisualData.h"



#define LOCTEXT_NAMESPACE "AssetTypeActions"

UClass* FAssetTypeActions_SettingUIDetailVisualData::GetSupportedClass() const
{
	return USettingUIDetailVisualData::StaticClass();
}

FText FAssetTypeActions_SettingUIDetailVisualData::GetName() const
{
	return LOCTEXT("SettingUIDetailVisualData", "Setting UI Detail Visual Data");
}

FColor FAssetTypeActions_SettingUIDetailVisualData::GetTypeColor() const
{
	return FColor(153, 0, 51);
}

uint32 FAssetTypeActions_SettingUIDetailVisualData::GetCategories()
{
	return EAssetTypeCategories::UI;
}

const TArray<FText>& FAssetTypeActions_SettingUIDetailVisualData::GetSubMenus() const
{
	static const TArray<FText> SubMenus
	{
		LOCTEXT("SettingUISubMenu", "Setting UI")
	};

	return SubMenus;
}

#undef LOCTEXT_NAMESPACE
