// Fill out your copyright notice in the Description page of Project Settings.

#include "BuzzAroundHUD.h"

#include "BuzzAround/UI/WidgetController/BuzzAroundOverlayWidgetController.h"

UBuzzAroundOverlayWidgetController* ABuzzAroundHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UBuzzAroundOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	
	return OverlayWidgetController;
}

void ABuzzAroundHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC,
	UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass unitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWdigetControllerClass unitialized, please fill out BP_AuraHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UBuzzAroundUserWidget>(Widget);
	
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UBuzzAroundOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	OverlayWidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}
