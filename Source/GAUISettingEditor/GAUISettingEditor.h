﻿// Copyright (C) 2024 owoDra

#pragma once

#include "Modules/ModuleManager.h"

#include "AssetTypeCategories.h"
#include "AssetTypeActions_Base.h"
#include "IAssetTools.h"


/**
 *  Modules for the editor features of the Game UI: Setting Addon plugin
 */
class FGAUISettingEditorModule : public IModuleInterface
{
public:
	//
	// Module name used to load/unload PropertyEditorModule
	//
	inline static const FName NAME_PropertyEditorModule{ TEXT("PropertyEditor") };

	//
	// Module name used to load/unload AssetToolsModule
	//
	inline static const FName NAME_AssetToolsModule{ TEXT("AssetTools") };

public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


protected:
	/**
	 *  Register PropertyCustomizations in the module
	 */
	void RegisterPropertyCustomizations();

	/**
	 *  Unregister PropertyCustomizations from the module
	 */
	void UnregisterPropertyCustomizations();


protected:
	//
	// Registered AssetTypeActions
	//
	TArray<TSharedPtr<FAssetTypeActions_Base>> RegisteredAssetTypeActions;

protected:
	/**
	 * Register AssetTypeActions in the module
	 */
	void RegisterAssetTypeActions();

	/**
	 * Unregister AssetTypeActions from the module
	 */
	void UnregisterAssetTypeActions();

	template<typename T>
	void RegisterAsset(TArray<TSharedPtr<FAssetTypeActions_Base>>& InOutRegisteredAssets)
	{
		TSharedPtr<T> SettingsDataTableAction{ MakeShared<T>() };
		IAssetTools::Get().RegisterAssetTypeActions(SettingsDataTableAction.ToSharedRef());
		InOutRegisteredAssets.Emplace(MoveTemp(SettingsDataTableAction));
	}

	void UnregisterAssets(TArray<TSharedPtr<FAssetTypeActions_Base>>& RegisteredAssets);
};


