// Copyright (C) 2024 owoDra

#include "SettingUISubsystem.h"

#include "SettingUIDeveloperSettings.h"
#include "Resolver/SettingUITypeResolver.h"
#include "Register/SettingUICustomRegister.h"

#include "GSCGameUserSettings.h"

#include "Engine/DataTable.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUISubsystem)


// Initialization

void USettingUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadStartupSettings();
}

void USettingUISubsystem::Deinitialize()
{
	Super::Deinitialize();

	RemoveAllSettingTable();
}

bool USettingUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	TArray<UClass*> ChildClasses;
	GetDerivedClasses(GetClass(), ChildClasses, false);

	// Only create an instance if there is no override implementation defined elsewhere

	return ChildClasses.Num() == 0;
}

void USettingUISubsystem::LoadStartupSettings()
{
	const auto* DevSetting{ GetDefault<USettingUIDeveloperSettings>() };

	for (const auto& KVP : DevSetting->StartupSettingTables)
	{
		const auto& TableTag{ KVP.Key };
		const auto* LoadedObject{ KVP.Value.TryLoad() };

		if (const auto* TableObject{ Cast<UDataTable>(LoadedObject) })
		{
			AddSettingTable(TableTag, TableObject);
		}
		else if (const auto* CustomRegister{ Cast<USettingUICustomRegister>(LoadedObject) })
		{
			AddSettingCustomTable(TableTag, CustomRegister);
		}
	}
}


// Setting Tables

void USettingUISubsystem::AddSettingTable(FGameplayTag TableTag, const UDataTable* InSettingTable)
{
	if (TableTag.IsValid() && InSettingTable && !SettingTables.Contains(TableTag))
	{
		FRegisteredSettingUITable NewTable;

		InSettingTable->ForeachRow<FSettingUIOption>(FString(),
			[this, &NewTable](const FName& Key, const FSettingUIOption& Value)
			{
				if(!NewTable.Row.Contains(Key) && !Value.bDeprecated)
				{
					if (auto* NewResolver{ NewObject<USettingUITypeResolver>(this, Value.Accessor.Type) })
					{
						NewResolver->InitializeResolver(this, Key, Value);
						NewTable.Row.Add(Key, NewResolver);
					}
				}
			}
		);

		SettingTables.Add(TableTag, NewTable);
	}
}

void USettingUISubsystem::AddSettingCustomTable(FGameplayTag TableTag, const USettingUICustomRegister* InCustomRegister)
{
	if (TableTag.IsValid() && InCustomRegister && !SettingTables.Contains(TableTag))
	{
		SettingTables.Add(TableTag, InCustomRegister->CreateTable(this));
	}
}

void USettingUISubsystem::RemoveSettingTable(FGameplayTag TableTag)
{
	if (TableTag.IsValid())
	{
		if (auto* FoundTable{ SettingTables.Find(TableTag) })
		{
			for (auto& KVP : FoundTable->Row)
			{
				if (const auto& Setting{ KVP.Value })
				{
					Setting->ReleaseResolver();
				}
			}

			FoundTable->Row.Empty();
		}

		SettingTables.Remove(TableTag);
	}
}

void USettingUISubsystem::RemoveAllSettingTable()
{
	for (auto TableIt{ SettingTables.CreateIterator() }; TableIt; ++TableIt)
	{
		for (auto RowIt{ TableIt->Value.Row.CreateIterator() }; RowIt; ++RowIt)
		{
			if (auto Resolver{ RowIt->Value })
			{
				Resolver->ReleaseResolver();
			}

			RowIt.RemoveCurrent();
		}

		TableIt.RemoveCurrent();
	}
}

void USettingUISubsystem::GetTableSettings(FGameplayTag TableTag, TArray<USettingUITypeResolver*>& OutArray) const
{
	if (TableTag.IsValid())
	{
		if (auto* FoundTable{ SettingTables.Find(TableTag) })
		{
			TArray<TObjectPtr<USettingUITypeResolver>> TempArray;
			FoundTable->Row.GenerateValueArray(TempArray);
			OutArray = TempArray;
		}
	}
}

void USettingUISubsystem::NotifySettingsUpdate(const TSet<FName>& SettingNames)
{
	for (const auto& TableKVP : SettingTables)
	{
		for (const auto& SettingToUpdate : SettingNames)
		{
			if (auto Setting{ TableKVP.Value.Row.FindRef(SettingToUpdate) })
			{
				Setting->ReEvaluateOption();
			}
		}
	}
}

void USettingUISubsystem::NotifyAllSettingsUpdate()
{
	for (const auto& TableKVP : SettingTables)
	{
		for (const auto& SettingKVP : TableKVP.Value.Row)
		{
			if (auto& Setting{ SettingKVP.Value })
			{
				Setting->ReEvaluateOption();
			}
		}
	}
}
