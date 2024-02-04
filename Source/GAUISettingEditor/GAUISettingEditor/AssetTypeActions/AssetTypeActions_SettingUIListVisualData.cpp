// Copyright (C) 2024 owoDra

#include "AssetTypeActions_SettingUIListVisualData.h"

#include "Widget/ListView/SettingUIListVisualData.h"


#define LOCTEXT_NAMESPACE "AssetTypeActions"

UClass* FAssetTypeActions_SettingUIListVisualData::GetSupportedClass() const
{
	return USettingUIListVisualData::StaticClass();
}

FText FAssetTypeActions_SettingUIListVisualData::GetName() const
{
	return LOCTEXT("SettingUIListVisualData", "Setting UI List Visual Data");
}

FColor FAssetTypeActions_SettingUIListVisualData::GetTypeColor() const
{
	return FColor(153, 0, 51);
}

uint32 FAssetTypeActions_SettingUIListVisualData::GetCategories()
{
	return EAssetTypeCategories::UI;
}

const TArray<FText>& FAssetTypeActions_SettingUIListVisualData::GetSubMenus() const
{
	static const TArray<FText> SubMenus
	{
		LOCTEXT("SettingUISubMenu", "Setting UI")
	};

	return SubMenus;
}

#undef LOCTEXT_NAMESPACE
