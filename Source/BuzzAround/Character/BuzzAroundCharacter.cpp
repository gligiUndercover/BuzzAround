// Fill out your copyright notice in the Description page of Project Settings.


#include "BuzzAroundCharacter.h"

#include "BuzzAround/Player/BuzzAroundPlayerController.h"
#include "BuzzAround/Player/BuzzAroundPlayerState.h"
#include "BuzzAround/UI/HUD/BuzzAroundHUD.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"


class ABuzzAroundHUD;
// Sets default values
ABuzzAroundCharacter::ABuzzAroundCharacter()
{
	//Get the Character movement comp
	CharacterMovementComp = GetCharacterMovement();
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	// CharacterMovementComp->MaxFlySpeed = CharacterMaxFlySpeed;
	// CharacterMovementComp->MaxAcceleration = CharacterMaxAcceleration;
	// CharacterMovementComp->BrakingDecelerationFlying = CharacterBrakingDecelerationFlying;
	// CharacterMovementComp->AirControl = CharacterAirControl;

	//create collusion shpere
	RootSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootSphereComponent"));
	RootSphereComponent->SetupAttachment(RootComponent);
	RootSphereComponent->SetSphereRadius(100.0f); // Adjust the radius as needed

	// Attach the existing skeletal mesh to the sphere component
	GetMesh()->SetupAttachment(RootSphereComponent);

	//set initial to be used for rotation of collision sphere on mouse by galin
	InitialRotation = RootSphereComponent->GetRelativeRotation();
	//Initilize TargetRotation by galin
	TargetRotation = InitialRotation; 
	bCanRotateBack = false;
	

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ABuzzAroundCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Character is Possessed!"));

	//Initialize ability actor info for the server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void ABuzzAroundCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Initialize ability actor info for the client
	InitAbilityActorInfo();
}

void ABuzzAroundCharacter::InitAbilityActorInfo()
{
	ABuzzAroundPlayerState* BuzzAroundPlayerState = GetPlayerState<ABuzzAroundPlayerState>();
	check(BuzzAroundPlayerState);

	AbilitySystemComponent = BuzzAroundPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(BuzzAroundPlayerState, this);
	Cast<UBuzzAroundAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	
	
	AttributeSet = BuzzAroundPlayerState->GetAttributeSet();

	if (ABuzzAroundPlayerController* BuzzAroundPlayerController = Cast<ABuzzAroundPlayerController>(GetController()))
	{
		if (ABuzzAroundHUD* BuzzAroundHUD = Cast<ABuzzAroundHUD>(BuzzAroundPlayerController->GetHUD()))
		{
			BuzzAroundHUD->InitOverlay(BuzzAroundPlayerController, BuzzAroundPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitAttributes();
}


// Update rotation
void ABuzzAroundCharacter::UpdateRotation(float LookAxisX)
{
	GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, "Called Update Rotation on PLayer BP");
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	bCanRotateBack = false;
	
	// Smoothly interpolate to the target rotation
	TargetRotation.Roll = FMath::Clamp(InitialRotation.Roll + (LookAxisX * 30.0f), -30.f, 30.0f);
	InitialRotation = FMath::RInterpTo(InitialRotation, TargetRotation, DeltaTime, 10);
	RootSphereComponent->SetRelativeRotation(InitialRotation);
	
	
	//Sets timer to wait for a second before invoking rotation back to Roll = 0.0f	
	if (InitialRotation.Roll> 0.3f)
	{
		GetWorldTimerManager().SetTimer(RotationBackHandle, this, &ABuzzAroundCharacter::ResetRotation, 1.0f, false, 1.0f);
	}

	
}

// sets a timer to continously update Roll to 0.0
void ABuzzAroundCharacter::ResetRotation()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	InitialRotation = RootSphereComponent->GetRelativeRotation();
	TargetRotation = FRotator(InitialRotation.Pitch, InitialRotation.Yaw, 0.0f);

	UE_LOG(LogTemp, Warning, TEXT("InitialRotation: %s, TargetRotation: %s"), *InitialRotation.ToString(), *TargetRotation.ToString());
	GetWorldTimerManager().SetTimer(RotationTimerHandle , this, &ABuzzAroundCharacter::UpdateRotation, 0.01f, true, 0.01f);

	///clears timer set in UpdateRotation
	GetWorld()->GetTimerManager().ClearTimer(RotationBackHandle);

}

//updates roll back to 0.00 and clears timer
void ABuzzAroundCharacter::UpdateRotation()
	{
		float DeltaTime = GetWorld()->GetDeltaSeconds(); // This gives the actual delta time between frames
		FRotator CurrentRotation = RootSphereComponent->GetRelativeRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 5.0f);

		UE_LOG(LogTemp, Warning, TEXT("CurrentRotation: %s, NewRotation: %s"), *CurrentRotation.ToString(), *NewRotation.ToString());

		RootSphereComponent->SetRelativeRotation(NewRotation);

		if (FMath::IsNearlyEqual(CurrentRotation.Roll, 0.0f, 0.01f))
		{
			UE_LOG(LogTemp, Warning, TEXT("Rotation finished, clearing timer"));
			GetWorld()->GetTimerManager().ClearTimer(RotationTimerHandle);
		}
	}


