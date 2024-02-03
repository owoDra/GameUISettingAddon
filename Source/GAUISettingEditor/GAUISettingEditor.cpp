﻿// Copyright (C) 2024 owoDra

#include "GAUISettingEditor.h"

#include "PropertyCustom_SettingUIOptionAccessor.h"

IMPLEMENT_MODULE(FGAUISettingEditorModule, GAUISettingEditor)


void FGAUISettingEditorModule::StartupModule()
{
	RegisterPropertyCustomizations();
	RegisterAssetTypeActions();
}

void FGAUISettingEditorModule::ShutdownModule()
{
	UnregisterPropertyCustomizations();
	UnregisterAssetTypeActions();
}


void FGAUISettingEditorModule::RegisterPropertyCustomizations()
{
	if (!FModuleManager::Get().IsModuleLoaded(NAME_PropertyEditorModule))
	{
		return;
	}

	auto& PropertyModule{ FModuleManager::LoadModuleChecked<FPropertyEditorModule>(NAME_PropertyEditorModule) };

	FPropertyCustom_SettingUIOptionAccessor::RegisterToPropertyEditorModule(PropertyModule);
}

void FGAUISettingEditorModule::UnregisterPropertyCustomizations()
{
	if (!FModuleManager::Get().IsModuleLoaded(NAME_PropertyEditorModule))
	{
		return;
	}

	auto& PropertyModule{ FModuleManager::LoadModuleChecked<FPropertyEditorModule>(NAME_PropertyEditorModule) };

	FPropertyCustom_SettingUIOptionAccessor::UnregisterToPropertyEditorModule(PropertyModule);
}


void FGAUISettingEditorModule::RegisterAssetTypeActions()
{
}

void FGAUISettingEditorModule::UnregisterAssetTypeActions()
{
	UnregisterAssets(RegisteredAssetTypeActions);
}

void FGAUISettingEditorModule::UnregisterAssets(TArray<TSharedPtr<FAssetTypeActions_Base>>& RegisteredAssets)
{
	const auto* AssetToolsPtr{ FModuleManager::GetModulePtr<FAssetToolsModule>(NAME_AssetToolsModule) };
	if (!AssetToolsPtr)
	{
		return;
	}

	auto& AssetTools{ AssetToolsPtr->Get() };
	for (auto& AssetTypeActionIt : RegisteredAssets)
	{
		if (AssetTypeActionIt.IsValid())
		{
			AssetTools.UnregisterAssetTypeActions(AssetTypeActionIt.ToSharedRef());
		}
	}
}
