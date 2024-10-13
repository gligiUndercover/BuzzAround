// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BuzzAroundPlayerController.generated.h"

class ABuzzAroundCharacter;
class UBuzzAroundAbilitySystemComponent;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class BUZZAROUND_API ABuzzAroundPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABuzzAroundPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> BuzzAroundContext;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY()
	TObjectPtr<ABuzzAroundCharacter> BuzzAroundCharacter;

	void Move(const struct FInputActionValue& InputActionValue);
	void Look(const struct FInputActionValue& InputActionValue);

	UPROPERTY()
	TObjectPtr<UBuzzAroundAbilitySystemComponent> BuzzAroundAbilitySystemComponent;

	UBuzzAroundAbilitySystemComponent* GetASC();
};
