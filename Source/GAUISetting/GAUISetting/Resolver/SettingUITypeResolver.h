// Copyright (C) 2024 owoDra

#pragma once

#include "Type/SettingUIOptionTypes.h"
#include "Type/SettingUIEditTypes.h"

#include "SettingUITypeResolver.generated.h"

class USettingUISubsystem;


/**
 * Class for processing between parameters of each setting item and UI
 * 
 * Tips:
 *	Derivations of this class can be created and adapted for each type of configuration item.
 * 
 * Note:
 *	Be sure to create the following UFunctions in derived classes.
 *	
 *	 - static [TYPE] GetterTemplate()
 *	 - static void SetterTemplate([TYPE] Arg)
 *	 - static TArray<[TYPE]> OptionGetterTemplate()
 */
UCLASS(Abstract, BlueprintType, NotBlueprintable)
class GAUISETTING_API USettingUITypeResolver : public UObject
{
	GENERATED_BODY()
public:
	USettingUITypeResolver(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#if WITH_EDITOR
public:
	/**
	 * Returns the UFunction of the getter's template function
	 */
	static UFunction* GetGetterTemplate(const UClass* ResolverClass);

	/**
	 * Returns the UFunction of the getter's template function
	 */
	static UFunction* GetSetterTemplate(const UClass* ResolverClass);

	/**
	 * Returns the UFunction of the getter's template function
	 */
	static UFunction* GetOptionGetterTemplate(const UClass* ResolverClass);
#endif

	////////////////////////////////////////////////////////////////////////
	// Initialization
protected:
	UPROPERTY(Transient)
	TWeakObjectPtr<USettingUISubsystem> OwnerSubsystem{ nullptr };

	UPROPERTY(Transient)
	FName DevName{ NAME_None };

	UPROPERTY(Transient)
	FSettingUIOption Data;

public:
	virtual void InitializeResolver(USettingUISubsystem* Subsystem, const FName& InDevName, const FSettingUIOption& OptionData);
	virtual void ReleaseResolver();
	virtual void ReEvaluateOption();


	////////////////////////////////////////////////////////////////////////
	// UI Data
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Info")
	virtual const FName& GetDevName() const { return DevName; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Info")
	virtual const FText& GetDisplayName() const { return Data.Name; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Info")
	virtual const FText& GetDescription() const { return Data.Description; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Info")
	virtual const FText& GetCategory() const { return Data.Category; }


	////////////////////////////////////////////////////////////////////////
	// Setting Data
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FPropertyValueChangeDelegate, USettingUITypeResolver*);
	FPropertyValueChangeDelegate OnPropertyValueChange;

protected:
	virtual FString GetPropertyValueAsString() const;
	virtual bool SetPropertyValueFromString(const FString& StringValue);

	void NotifyPropertyValueChange(bool bBroadcastDependancies = false);


	////////////////////////////////////////////////////////////////////////
	// Editable State
protected:
	UPROPERTY(Transient)
	FSettingUIEditableState EditableState{ FSettingUIEditableState::Editable };

	UPROPERTY(Transient)
	TObjectPtr<USettingUIEditCondition> EditCondition{ nullptr };

public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FEditableStateChangeDelegate, USettingUITypeResolver*, const FSettingUIEditableState&);
	FEditableStateChangeDelegate OnEditStateChange;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Editable State")
	virtual const FSettingUIEditableState& GetEditableState() const { return EditableState; }

protected:
	virtual void UpdateEditableState();

};
