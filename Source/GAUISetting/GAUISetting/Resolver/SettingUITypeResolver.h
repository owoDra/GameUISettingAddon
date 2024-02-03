// Copyright (C) 2024 owoDra

#pragma once

#include "Type/SettingUIOptionTypes.h"

#include "SettingUITypeResolver.generated.h"

class UGSCSubsystem;


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
public:
	virtual void InitializeResolver(const FSettingUIOption& OptionData);


	////////////////////////////////////////////////////////////////////////
	// UI Data
protected:
	UPROPERTY(Transient)
	FText DisplayName;

	UPROPERTY(Transient)
	FText Description;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Info")
	virtual const FText& GetDisplayName() const { return DisplayName; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Info")
	virtual const FText& GetDescription() const { return Description; }


	////////////////////////////////////////////////////////////////////////
	// Setting Data
protected:
	UPROPERTY(Transient)
	TWeakObjectPtr<UGSCSubsystem> SourceSubsystem{ nullptr };

	UPROPERTY(Transient)
	FName GetterName{ NAME_None };

	UPROPERTY(Transient)
	FName SetterName{ NAME_None };

	UPROPERTY(Transient)
	FName OptionGetterName{ NAME_None };

protected:
	virtual FString GetPropertyValueAsString() const;
	virtual bool SetPropertyValueFromString(const FString& StringValue);


	////////////////////////////////////////////////////////////////////////
	// Utilities
protected:
	template<typename T>
	T* GetSourceSubsystem() const
	{
		return Cast<T>(SourceSubsystem.Get());
	}

};
