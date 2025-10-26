// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Bases/BaseUserWidget.h"
#include "MainHUDWidget.generated.h"

class UGameSpeedControlWidget;

UCLASS()
class WYLDFORT_API UMainHUDWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="HUD")
    void SetTopRightContent(UWidget* Content);
	UFUNCTION(BlueprintCallable, Category="HUD")
    void SetTopLeftContent(UWidget* Content);
	UFUNCTION(BlueprintCallable, Category="HUD")
    void SetBottomRightContent(UWidget* Content);
	UFUNCTION(BlueprintCallable, Category="HUD")
    void SetBottomLeftContent(UWidget* Content);


private:
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<class UNamedSlot> TopLeftArea;
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<class UNamedSlot> TopRightArea;
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<class UNamedSlot> BottomLeftArea;
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<class UNamedSlot> BottomRightArea;

	void InstantiateWidgets();
	void InstantiateTopRight();
	void InstantiateTopLeft();
	void InstantiateBottomRight();
	void InstantiateBottomLeft();

	// Game Speed Controls
	UPROPERTY(EditDefaultsOnly, Category="HUD|Classes")
    TSubclassOf<UGameSpeedControlWidget> TimeControlsClass;
    UPROPERTY(Transient)
    TObjectPtr<UGameSpeedControlWidget> TimeControlsInstance;


};
