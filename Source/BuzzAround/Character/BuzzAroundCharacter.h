// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuzzAroundCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BuzzAroundCharacter.generated.h"

UCLASS()
class BUZZAROUND_API ABuzzAroundCharacter : public ABuzzAroundCharacterBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ABuzzAroundCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

private:
	virtual void InitAbilityActorInfo() override;
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComp;
};
