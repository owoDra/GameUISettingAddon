// Copyright (C) 2024 owoDra

#include "SettingUITable.h"

#include "Type/SettingUIOptionTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUITable)


USettingUITable::USettingUITable()
{
	RowStruct = FSettingUIOption::StaticStruct();
}

#if WITH_EDITOR
TArray<FName> USettingUITable::GetDefinedSettingNames()
{
	TArray<FName> OutArray;

	for (TObjectIterator<USettingUITable> It; It; ++It)
	{
		OutArray.Append(It->GetRowNames());
	}

	return OutArray;
}
#endif
