// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuzzAroundCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* RootSphereComponent;

	// Function to update rotation roll based on mouse input from the controller
	void UpdateRotation(float LookAxisX);

	// Function to reset rotation (Rotate back) to initial state
	void ResetRotation();

	//Funtion to rotate back smoothly
	void UpdateRotation();
	
	FRotator InitialRotation;
	FRotator TargetRotation;
	float RotationSpeed = 2.0f; // Adjust as needed

private:
	virtual void InitAbilityActorInfo() override;
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComp;
		

protected:
	//True if the Rotation Back (i.e. ResetRotation) to Roll 0.00 should happen
	bool bCanRotateBack;

	//Handles the delay to rotate back (i.e. ResetRotation) to Roll 0.00
	FTimerHandle RotationBackHandle;

	//Handles the looping rotation to make sure Roll interpolates to 0.01 all the way
	FTimerHandle RotationTimerHandle;

};
