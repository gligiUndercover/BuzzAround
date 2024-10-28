// Fill out your copyright notice in the Description page of Project Settings.


#include "BuzzAroundPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BuzzAround/AbilitySystem/BuzzAroundAbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "BuzzAround/Character/BuzzAroundCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


ABuzzAroundPlayerController::ABuzzAroundPlayerController()
{
	bReplicates = true;
}

void ABuzzAroundPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	
	if (BuzzAroundCharacter)
	{
		// Get the control rotation, which represents the camera/character's facing direction
		FRotator ControllerRotation = BuzzAroundCharacter->GetControlRotation();
        
		// Convert the rotator to a direction vector (forward vector)
		FVector FacingDirection = ControllerRotation.Vector();

		// Display the facing direction on screen
		FString FacingDirectionText = FString::Printf(TEXT("Facing Direction: X=%.2f, Y=%.2f, Z=%.2f"), FacingDirection.X, FacingDirection.Y, FacingDirection.Z);
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, FacingDirectionText);
						
		

	}
}

void ABuzzAroundPlayerController::BeginPlay()
{
	Super::BeginPlay();

	BuzzAroundCharacter = Cast<ABuzzAroundCharacter>(GetPawn());
	if (BuzzAroundCharacter) GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Green, "Charcater is NOT nullptr");
	check(BuzzAroundContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem && BuzzAroundContext)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Input Mapping Context added!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Subsystem or BuzzAroundContext is NULL!");
	}
	
	if (Subsystem)
	{
		Subsystem->AddMappingContext(BuzzAroundContext, 0);
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABuzzAroundPlayerController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABuzzAroundPlayerController::Look);		

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Input Actions Bound!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "EnhancedInputComponent is NULL!");
	}

}

void ABuzzAroundPlayerController::Look(const FInputActionValue& Value)
{

	FVector LookAxisVector = Value.Get<FVector>();
	if (nullptr != BuzzAroundCharacter)
	{
		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, "Inside the Look callback");

		if (LookAxisVector.X != 0.0f)
		{
			//adds Yaw to character
			BuzzAroundCharacter->AddControllerYawInput(LookAxisVector.X);
			BuzzAroundCharacter->UpdateRotation(LookAxisVector.X);
			
			GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, "Inside the custom update rotation in the controller");
		}
		//adds Pitch to character
		BuzzAroundCharacter->AddControllerPitchInput(LookAxisVector.Y);
	}
		
}



void ABuzzAroundPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (nullptr != BuzzAroundCharacter)
	{
		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Blue, "Inside the Move callback");
		if (BuzzAroundCharacter->GetCharacterMovement()->MovementMode != EMovementMode::MOVE_Flying) BuzzAroundCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		
		if (!BuzzAroundCharacter->GetCharacterMovement()->IsFlying())
		{
			GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Red, TEXT("IsFlying is FALSE"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Green, TEXT("IsFlying is TRUE"));
		}
		// Get forward vector from the full control rotation (includes pitch and yaw)
		const FVector ForwardDirection = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);

		// Get the right vector (perpendicular to forward)
		const FVector RightDirection = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y);

		// Get the up vector (aligned with the Z axis, for flying up/down)
		// const FVector UpDirection = FVector::UpVector;
		// const FVector UpDirection = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Z);
		
		// Move character based on input: X for forward/backward, Y for right/left, Z for up/down
		BuzzAroundCharacter->AddMovementInput(ForwardDirection, MovementVector.X); // Forward/Backward movement
		BuzzAroundCharacter->AddMovementInput(RightDirection, MovementVector.Y);   // Right/Left movement
		// AddMovementInput(UpDirection, MovementVector.Z);      // Up/Down movement (flying)
	}
}

UBuzzAroundAbilitySystemComponent* ABuzzAroundPlayerController::GetASC()
{
	if (nullptr == BuzzAroundAbilitySystemComponent)
	{
		BuzzAroundAbilitySystemComponent = Cast<UBuzzAroundAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
			GetPawn<APawn>()));
	}

	return BuzzAroundAbilitySystemComponent;
}
