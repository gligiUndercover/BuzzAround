// Fill out your copyright notice in the Description page of Project Settings.


#include "BuzzAroundOverlayWidgetController.h"

#include "BuzzAround/AbilitySystem/BuzzAroundAttributeSet.h"

void UBuzzAroundOverlayWidgetController::BroadcastInitialValues()
{
	const UBuzzAroundAttributeSet* BuzzAroundAttributeSet = CastChecked<UBuzzAroundAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(BuzzAroundAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(BuzzAroundAttributeSet->GetMaxHealth());
}

void UBuzzAroundOverlayWidgetController::BindCallbacksToDependencies()
{
	const UBuzzAroundAttributeSet* BuzzAroundAttributeSet = CastChecked<UBuzzAroundAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	BuzzAroundAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BuzzAroundAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);
}
