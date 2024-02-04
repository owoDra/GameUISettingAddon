// Copyright (C) 2024 owoDra

#pragma once

#include "SettingUIEditTypes.generated.h"


/**
 * Editable state of setting option
 */
USTRUCT(BlueprintType)
struct FSettingUIEditableState
{
	GENERATED_BODY()
public:
	FSettingUIEditableState() = default;

	FSettingUIEditableState(bool bInVisible, bool bInEnabled)
		: bVisible(bInVisible), bEnabled(bInEnabled)
	{}

	static const FSettingUIEditableState Editable;		// Visible and editable
	static const FSettingUIEditableState NotEditable;	// Visible but not editable
	static const FSettingUIEditableState Collapsed;		// Not Visble and not editable

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bVisible{ false };

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bEnabled{ false };

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FText> DisabledReasons;

public:
	bool operator==(const FSettingUIEditableState& Other) const { return (bVisible == Other.bVisible) && (bEnabled == Other.bEnabled); }

	bool IsEditable() const { return *this == FSettingUIEditableState::Editable; }
	bool IsDisabled() const { return *this == FSettingUIEditableState::NotEditable; }
	bool IsCollapsed() const { return *this == FSettingUIEditableState::Collapsed; }

	void Hide();
	void Disable(const FText& Reason);

};
