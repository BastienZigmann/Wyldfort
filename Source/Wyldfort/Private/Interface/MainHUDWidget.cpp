// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/MainHUDWidget.h"
#include "Interface/GameSpeedControlWidget.h"
#include "Components/NamedSlot.h"

void UMainHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();

    InstantiateWidgets();
}

void UMainHUDWidget::SetTopRightContent(UWidget* Content)
{
    if (!TopRightArea || !Content) return;
    TopRightArea->SetContent(Content);
}

void UMainHUDWidget::SetTopLeftContent(UWidget* Content)
{
    if (!TopLeftArea || !Content) return;
    TopLeftArea->SetContent(Content);
}

void UMainHUDWidget::SetBottomRightContent(UWidget* Content)
{
    if (!BottomRightArea || !Content) return;
    BottomRightArea->SetContent(Content);
}

void UMainHUDWidget::SetBottomLeftContent(UWidget* Content)
{
    if (!BottomLeftArea || !Content) return;
    BottomLeftArea->SetContent(Content);
}

void UMainHUDWidget::InstantiateWidgets()
{
    InstantiateTopRight();
    InstantiateTopLeft();
    InstantiateBottomRight();
    InstantiateBottomLeft();
}

void UMainHUDWidget::InstantiateTopRight()
{
    if (!TopRightArea)
    {
        ErrorLog("TopRightArea is null, cannot instantiate TimeControlsInstance.", this);
        return;
    }
    if (!TimeControlsClass)
    {
        WarningLog("TimeControlsClass is not set, cannot instantiate TimeControlsInstance.", this);
        return;
    }

    TimeControlsInstance = CreateWidget<UGameSpeedControlWidget>(this, TimeControlsClass);
    if (TimeControlsInstance)
    {
        TopRightArea->SetContent(TimeControlsInstance);
    }
}

void UMainHUDWidget::InstantiateTopLeft()
{
    if (!TopLeftArea)  
    {
        ErrorLog("TopLeftArea is null, cannot instantiate widgets.", this);
        return;
    }
}

void UMainHUDWidget::InstantiateBottomRight()
{
    if (!BottomRightArea)
    {
        ErrorLog("BottomRightArea is null, cannot instantiate widgets.", this);
        return;
    }
}

void UMainHUDWidget::InstantiateBottomLeft()
{
    if (!BottomLeftArea)
    {
        ErrorLog("BottomLeftArea is null, cannot instantiate widgets.", this);
        return;
    }
}
