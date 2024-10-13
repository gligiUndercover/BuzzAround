// Fill out your copyright notice in the Description page of Project Settings.


#include "BuzzAroundUserWidget.h"

void UBuzzAroundUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
