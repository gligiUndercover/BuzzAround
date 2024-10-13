// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BuzzAroundHUD.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;
class UBuzzAroundOverlayWidgetController;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UBuzzAroundUserWidget;
/**
 * 
 */
UCLASS()
class BUZZAROUND_API ABuzzAroundHUD : public AHUD
{
	GENERATED_BODY()

public:
	//Getters for the controllers in the private section below:
	UBuzzAroundOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	//The actual widget stored
	UPROPERTY()
	TObjectPtr<UBuzzAroundUserWidget> OverlayWidget;
	
	//This is needed to construct a new Widget of any kind - this is why its a TSubclassOfType
	//This is the one we actually do as BP, this is why its EditAnywhere
	UPROPERTY(EditAnywhere)
	TSubclassOf<UBuzzAroundUserWidget> OverlayWidgetClass;

	//Here below follow the same pair of widget/widget class
	UPROPERTY()
	TObjectPtr<UBuzzAroundOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UBuzzAroundOverlayWidgetController> OverlayWidgetControllerClass;
};
