// Copyright (C) 2024 owoDra

#pragma once

#include "SettingUITypeResolver.h"

#include "SettingUITypeResolver_Scalar.generated.h"


/**
 * Base resolver class for "Scalar" type setting option
 */
UCLASS(Abstract)
class GAUISETTING_API USettingUITypeResolver_Scalar : public USettingUITypeResolver
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Scalar(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "UI")
	virtual int32 GetFractionDigits() const PURE_VIRTUAL(, return 0;);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "UI")
	virtual float GetStep() const PURE_VIRTUAL(, return 0.0f;);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "UI")
	virtual float GetMaxValue() const PURE_VIRTUAL(, return 0.0f;);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "UI")
	virtual float GetMinValue() const PURE_VIRTUAL(, return 0.0f;);

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Setting")
	virtual void SetSettingValue(float NewValue) PURE_VIRTUAL(, );

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Setting")
	virtual float GetSettingValue() const PURE_VIRTUAL(, return 0.0;);

};


/**
 * Resolver class for "Switch(Float)" type setting option
 */
UCLASS(Blueprintable, meta = (DisplayName = "Float Scalar Resolver"))
class USettingUITypeResolver_Scalar_Float final : public USettingUITypeResolver_Scalar
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Scalar_Float(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	////////////////////////////////////////////////////////////////////////////
	// Template Functions
#if WITH_EDITOR
public:
	UFUNCTION()
	static float GetterTemplate() { return 0.0f; }

	UFUNCTION()
	static void SetterTemplate(float Arg) {}
#endif


	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	int32 FractionDigits{ 1 };

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	float Step{ 0.0f };

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	float MaxValue{ 1.0f };

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	float MinValue{ 0.0f };

public:
	virtual float GetStep() const { return Step; }
	virtual int32 GetFractionDigits() const { return FractionDigits; }
	virtual float GetMaxValue() const { return MaxValue; }
	virtual float GetMinValue() const { return MinValue; }

	virtual void SetSettingValue(float NewValue) override;
	virtual float GetSettingValue() const override;

};


/**
 * Resolver class for "Switch(Int)" type setting option
 */
UCLASS(Blueprintable, meta = (DisplayName = "Int Scalar Resolver"))
class USettingUITypeResolver_Scalar_Int final : public USettingUITypeResolver_Scalar
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Scalar_Int(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	////////////////////////////////////////////////////////////////////////////
	// Template Functions
#if WITH_EDITOR
public:
	UFUNCTION()
	static int32 GetterTemplate() { return 0; }

	UFUNCTION()
	static void SetterTemplate(int32 Arg) {}
#endif


	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	int32 MaxValue{ 100 };

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	int32 MinValue{ 0 };

public:
	virtual float GetStep() const { return 1.0f; }
	virtual int32 GetFractionDigits() const { return 0; }
	virtual float GetMaxValue() const { return MaxValue; }
	virtual float GetMinValue() const { return MinValue; }

	virtual void SetSettingValue(float NewValue) override;
	virtual float GetSettingValue() const override;

};


/**
 * Resolver class for "Switch(Byte)" type setting option
 */
UCLASS(Blueprintable, meta = (DisplayName = "Byte Scalar Resolver"))
class USettingUITypeResolver_Scalar_Byte final : public USettingUITypeResolver_Scalar
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Scalar_Byte(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

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
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	uint8 MaxValue{ 255 };

	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	uint8 MinValue{ 0 };

public:
	virtual float GetStep() const { return 1.0f; }
	virtual int32 GetFractionDigits() const { return 0; }
	virtual float GetMaxValue() const { return MaxValue; }
	virtual float GetMinValue() const { return MinValue; }

	virtual void SetSettingValue(float NewValue) override;
	virtual float GetSettingValue() const override;

};
