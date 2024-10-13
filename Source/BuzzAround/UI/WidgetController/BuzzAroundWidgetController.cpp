// Fill out your copyright notice in the Description page of Project Settings.


#include "BuzzAroundWidgetController.h"

void UBuzzAroundWidgetController::SetWidgetControllerParams(const FWidgetControllerParams WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UBuzzAroundWidgetController::BroadcastInitialValues()
{
	//TODO: Empty for now
}

void UBuzzAroundWidgetController::BindCallbacksToDependencies()
{
	//TODO: Empty for now
}
