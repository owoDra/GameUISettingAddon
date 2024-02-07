// Copyright (C) 2024 owoDra

#pragma once

#include "SettingUITypeResolver_Switch.h"

#include "SettingUITypeResolver_Graphic.generated.h"


/**
 * Resolver class for "Switch(Resolution)" type setting option
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Resolution Switch Resolver"))
class GAUISETTING_API USettingUITypeResolver_Switch_Resolution : public USettingUITypeResolver_Switch
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Switch_Resolution(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
private:
	UPROPERTY(Transient)
	TArray<FText> OptionDisplayTexts;

	UPROPERTY(Transient)
	TArray<FIntPoint> OptionValues;

protected:
	virtual void NotifyPropertyOptionChange() override;

public:
	virtual void SetSettingValue(int32 NewValue) override;
	virtual int32 GetSettingValue() const override;

	virtual TArray<FText> GetOptionDisplayTexts() const override;

};


/**
 * Resolver class for "Switch(WindowMode)" type setting option
 */
UCLASS(Blueprintable, meta = (DisplayName = "Window Mode Switch Resolver"))
class GAUISETTING_API USettingUITypeResolver_Switch_WindowMode : public USettingUITypeResolver_Switch
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Switch_WindowMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
protected:
	UPROPERTY(EditDefaultsOnly, Transient, Category = "Setting")
	TArray<FText> OptionDisplayTexts;

	UPROPERTY(EditDefaultsOnly, Transient, Category = "Setting")
	TArray<TEnumAsByte<EWindowMode::Type>> OptionValues;

public:
	virtual void SetSettingValue(int32 NewValue) override;
	virtual int32 GetSettingValue() const override;

	virtual TArray<FText> GetOptionDisplayTexts() const override;

};


/**
 * Resolver class for "Switch(OverrallQuality)" type setting option
 */
UCLASS(Blueprintable, meta = (DisplayName = "Overrall Quality Switch Resolver"))
class GAUISETTING_API USettingUITypeResolver_Switch_OverrallQuality : public USettingUITypeResolver_Switch
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Switch_OverrallQuality(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
protected:
	UPROPERTY(EditDefaultsOnly, Transient, Category = "Setting")
	TArray<FText> OptionDisplayTexts;

	UPROPERTY(EditDefaultsOnly, Transient, Category = "Setting")
	TArray<int32> OptionValues;

public:
	virtual void SetSettingValue(int32 NewValue) override;
	virtual int32 GetSettingValue() const override;

	virtual TArray<FText> GetOptionDisplayTexts() const override;

};


/**
 * Resolver class for "Switch(Quality)" type setting option
 */
UCLASS(Blueprintable, meta = (DisplayName = "Quality Switch Resolver"))
class GAUISETTING_API USettingUITypeResolver_Switch_Quality : public USettingUITypeResolver_Switch
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Switch_Quality(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	////////////////////////////////////////////////////////////////////////////
	// Template Functions
#if WITH_EDITOR
public:
	UFUNCTION()
	static int32 GetterTemplate() { return false; }

	UFUNCTION()
	static void SetterTemplate(int32 Arg) {}
#endif


	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
protected:
	UPROPERTY(EditDefaultsOnly, Transient, Category = "Setting")
	TArray<FText> OptionDisplayTexts;

	UPROPERTY(EditDefaultsOnly, Transient, Category = "Setting")
	TArray<int32> OptionValues;

public:
	virtual void SetSettingValue(int32 NewValue) override;
	virtual int32 GetSettingValue() const override;

	virtual TArray<FText> GetOptionDisplayTexts() const override;

};


/**
 * Resolver class for "Switch(FrameRate)" type setting option
 */
UCLASS(Blueprintable, meta = (DisplayName = "Frame Rate Switch Resolver"))
class GAUISETTING_API USettingUITypeResolver_Switch_FrameRate : public USettingUITypeResolver_Switch
{
	GENERATED_BODY()
public:
	USettingUITypeResolver_Switch_FrameRate(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	////////////////////////////////////////////////////////////////////////////
	// Getter・Setter
protected:
	UPROPERTY(EditDefaultsOnly, Transient, Category = "Setting")
	TArray<FText> OptionDisplayTexts;

	UPROPERTY(EditDefaultsOnly, Transient, Category = "Setting")
	TArray<float> OptionValues;

public:
	virtual void SetSettingValue(int32 NewValue) override;
	virtual int32 GetSettingValue() const override;

	virtual TArray<FText> GetOptionDisplayTexts() const override;

};
