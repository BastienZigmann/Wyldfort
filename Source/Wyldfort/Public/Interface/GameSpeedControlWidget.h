// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Bases/BaseUserWidget.h"
#include "GameSpeedControlWidget.generated.h"

class UButton;

UCLASS()
class WYLDFORT_API UGameSpeedControlWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PauseButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PlayButton; // Basic speed
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Speed2Button;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Speed3Button;

private:

	UFUNCTION()
	void OnPauseClicked();
	UFUNCTION()
	void OnPlayClicked();
	UFUNCTION()
	void OnSpeed2Clicked();
	UFUNCTION()
	void OnSpeed3Clicked();

};
