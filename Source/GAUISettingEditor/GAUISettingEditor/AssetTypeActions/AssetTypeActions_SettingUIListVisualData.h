﻿// Copyright (C) 2024 owoDra

#pragma once

#include "AssetTypeActions_Base.h"


class FAssetTypeActions_SettingUIListVisualData : public FAssetTypeActions_Base
{
public:
	virtual UClass* GetSupportedClass() const override;

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	virtual const TArray<FText>& GetSubMenus() const override;

};
