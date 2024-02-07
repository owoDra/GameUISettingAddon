// Copyright (C) 2024 owoDra

#pragma once

#include "SettingUITypeResolver.h"

#include "SettingUITypeResolver_Switch.generated.h"


/**
 * Base resolver class for "Switch" type setting option
 */
UCLASS(Abstract)
class GAUISETTING_API USettingUITypeResolver_Switch : public USettingUITypeResolver
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Switch(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Setting")
	virtual void SetSettingValue(int32 NewValue) PURE_VIRTUAL(, );

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Setting")
	virtual int32 GetSettingValue() const PURE_VIRTUAL(, return 0;);

};


/**
 * Resolver class for "Switch(Bool)" type setting option
 */
UCLASS(Blueprintable, meta = (DisplayName = "Bool Switch Resolver"))
class USettingUITypeResolver_Switch_Bool final : public USettingUITypeResolver_Switch
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Switch_Bool(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	////////////////////////////////////////////////////////////////////////////
	// Template Functions
#if WITH_EDITOR
public:
	UFUNCTION()
	static bool GetterTemplate() { return false; }

	UFUNCTION()
	static void SetterTemplate(bool Arg) {}
#endif


	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	FText TrueText;

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	FText FalseText;

public:
	virtual void SetSettingValue(int32 NewValue) override;
	virtual int32 GetSettingValue() const override;

	virtual TArray<FText> GetOptionDisplayTexts() const override;

};


/**
 * Resolver class for "Switch(Float)" type setting option
 */
UCLASS(Blueprintable, meta = (DisplayName = "Float Switch Resolver"))
class USettingUITypeResolver_Switch_Float final : public USettingUITypeResolver_Switch
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Switch_Float(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	////////////////////////////////////////////////////////////////////////////
	// Template Functions
#if WITH_EDITOR
public:
	UFUNCTION()
	static float GetterTemplate() { return 0.0f; }

	UFUNCTION()
	static void SetterTemplate(float Arg) {}

	UFUNCTION()
	static TArray<float> OptionGetterTemplate() { return TArray<float>(); }
#endif


	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
protected:
	//
	// Conversion format for converting option values to text to be displayed in the UI
	// 
	// For Example:
	//	"{Value} cm"
	//	"{Value} secs"
	//	"x{Value}"
	//	"~ {Value}"
	//
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	FText OptionFormat;

private:
	UPROPERTY(Transient)
	TArray<FText> OptionDisplayTexts;

	UPROPERTY(Transient)
	TArray<float> OptionValues;

protected:
	virtual void NotifyPropertyOptionChange() override;

public:
	virtual void SetSettingValue(int32 NewValue) override;
	virtual int32 GetSettingValue() const override;

	virtual TArray<FText> GetOptionDisplayTexts() const override;

};


/**
 * Resolver class for "Switch(Double)" type setting option
 */
UCLASS(Blueprintable, meta = (DisplayName = "Double Switch Resolver"))
class USettingUITypeResolver_Switch_Double final : public USettingUITypeResolver_Switch
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Switch_Double(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	////////////////////////////////////////////////////////////////////////////
	// Template Functions
#if WITH_EDITOR
public:
	UFUNCTION()
	static double GetterTemplate() { return 0.0; }

	UFUNCTION()
	static void SetterTemplate(double Arg) {}

	UFUNCTION()
	static TArray<double> OptionGetterTemplate() { return TArray<double>(); }
#endif


	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
protected:
	//
	// Conversion format for converting option values to text to be displayed in the UI
	// 
	// For Example:
	//	"{Value} cm"
	//	"{Value} secs"
	//	"x{Value}"
	//	"~ {Value}"
	//
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	FText OptionFormat;

private:
	UPROPERTY(Transient)
	TArray<FText> OptionDisplayTexts;

	UPROPERTY(Transient)
	TArray<double> OptionValues;

protected:
	virtual void NotifyPropertyOptionChange() override;

public:
	virtual void SetSettingValue(int32 NewValue) override;
	virtual int32 GetSettingValue() const override;

	virtual TArray<FText> GetOptionDisplayTexts() const override;

};


/**
 * Resolver class for "Switch(Int)" type setting option
 */
UCLASS(Blueprintable, meta = (DisplayName = "Int Switch Resolver"))
class USettingUITypeResolver_Switch_Int final : public USettingUITypeResolver_Switch
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Switch_Int(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	////////////////////////////////////////////////////////////////////////////
	// Template Functions
#if WITH_EDITOR
public:
	UFUNCTION()
	static int32 GetterTemplate() { return 0; }

	UFUNCTION()
	static void SetterTemplate(int32 Arg) {}

	UFUNCTION()
	static TArray<int32> OptionGetterTemplate() { return TArray<int32>(); }
#endif


	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
protected:
	//
	// Conversion format for converting option values to text to be displayed in the UI
	// 
	// For Example:
	//	"{Value} cm"
	//	"{Value} secs"
	//	"x{Value}"
	//	"~ {Value}"
	//
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	FText OptionFormat;

private:
	UPROPERTY(Transient)
	TArray<FText> OptionDisplayTexts;

	UPROPERTY(Transient)
	TArray<int32> OptionValues;

protected:
	virtual void NotifyPropertyOptionChange() override;

public:
	virtual void SetSettingValue(int32 NewValue) override;
	virtual int32 GetSettingValue() const override;

	virtual TArray<FText> GetOptionDisplayTexts() const override;

};


/**
 * Resolver class for "Switch(String)" type setting option
 */
UCLASS(Blueprintable, meta = (DisplayName = "String Switch Resolver"))
class USettingUITypeResolver_Switch_String final : public USettingUITypeResolver_Switch
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Switch_String(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	////////////////////////////////////////////////////////////////////////////
	// Template Functions
#if WITH_EDITOR
public:
	UFUNCTION()
	static FString GetterTemplate() { return FString(); }

	UFUNCTION()
	static void SetterTemplate(FString Arg) {}

	UFUNCTION()
	static TArray<FString> OptionGetterTemplate() { return TArray<FString>(); }
#endif


	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
private:
	UPROPERTY(Transient)
	TArray<FText> OptionDisplayTexts;

	UPROPERTY(Transient)
	TArray<FString> OptionValues;

protected:
	virtual void NotifyPropertyOptionChange() override;

public:
	virtual void SetSettingValue(int32 NewValue) override;
	virtual int32 GetSettingValue() const override;

	virtual TArray<FText> GetOptionDisplayTexts() const override;

};


/**
 * Resolver class for "Switch(Byte)" type setting option
 */
UCLASS(Blueprintable, meta = (DisplayName = "Byte Switch Resolver"))
class USettingUITypeResolver_Switch_Byte final : public USettingUITypeResolver_Switch
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Switch_Byte(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	////////////////////////////////////////////////////////////////////////////
	// Template Functions
#if WITH_EDITOR
public:
	UFUNCTION()
	static uint8 GetterTemplate() { return 0; }

	UFUNCTION()
	static void SetterTemplate(uint8 Arg) {}

	UFUNCTION()
	static TArray<uint8> OptionGetterTemplate() { return TArray<uint8>(); }
#endif


	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
protected:
	//
	// Conversion format for converting option values to text to be displayed in the UI
	// 
	// For Example:
	//	"{Value} cm"
	//	"{Value} secs"
	//	"x{Value}"
	//	"~ {Value}"
	//
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	FText OptionFormat;

private:
	UPROPERTY(Transient)
	TArray<FText> OptionDisplayTexts;

	UPROPERTY(Transient)
	TArray<uint8> OptionValues;

protected:
	virtual void NotifyPropertyOptionChange() override;

public:
	virtual void SetSettingValue(int32 NewValue) override;
	virtual int32 GetSettingValue() const override;

	virtual TArray<FText> GetOptionDisplayTexts() const override;

};


/**
 * Resolver class for "Switch(Enum)" type setting option
 */
UCLASS(Blueprintable, meta = (DisplayName = "Enum Switch Resolver"))
class USettingUITypeResolver_Switch_Enum final : public USettingUITypeResolver_Switch
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Switch_Enum(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	////////////////////////////////////////////////////////////////////////////
	// Template Functions
#if WITH_EDITOR
public:
	UFUNCTION()
	static uint8 GetterTemplate() { return 0; }

	UFUNCTION()
	static void SetterTemplate(uint8 Arg) {}
#endif


	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
private:
	UPROPERTY(Transient)
	TArray<FText> OptionDisplayTexts;

	UPROPERTY(Transient)
	TArray<uint8> OptionValues;

protected:
	virtual void NotifyPropertyOptionChange() override;

private:
	const UEnum* GetPropertyAsEnum() const;

public:
	virtual void SetSettingValue(int32 NewValue) override;
	virtual int32 GetSettingValue() const override;

	virtual TArray<FText> GetOptionDisplayTexts() const override;

};
