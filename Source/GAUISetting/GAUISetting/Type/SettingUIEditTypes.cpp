// Copyright (C) 2024 owoDra

#include "SettingUIEditTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SettingUIEditTypes)


const FSettingUIEditableState FSettingUIEditableState::Editable{ /*bVisible = */ true, /*bEnabled = */ true };
const FSettingUIEditableState FSettingUIEditableState::NotEditable{ /*bVisible = */ true, /*bEnabled = */ false };
const FSettingUIEditableState FSettingUIEditableState::Collapsed{ /*bVisible = */ false, /*bEnabled = */ false };


void FSettingUIEditableState::Hide()
{
	bVisible = false;
}

void FSettingUIEditableState::Disable(const FText& Reason)
{
	bEnabled = false;
	DisabledReasons.Add(Reason);
}
