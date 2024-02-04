// Copyright (C) 2024 owoDra

#pragma once

#include "AssetTypeActions_CSVAssetBase.h"

class USettingUITable;


class FAssetTypeActions_SettingUITable : public FAssetTypeActions_CSVAssetBase
{
public:
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override { return EAssetTypeCategories::UI; }
	virtual const TArray<FText>& GetSubMenus() const override;

	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

};
