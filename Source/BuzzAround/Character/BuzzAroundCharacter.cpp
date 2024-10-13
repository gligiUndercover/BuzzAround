// Fill out your copyright notice in the Description page of Project Settings.


#include "BuzzAroundCharacter.h"

#include "BuzzAround/Player/BuzzAroundPlayerController.h"
#include "BuzzAround/Player/BuzzAroundPlayerState.h"
#include "BuzzAround/UI/HUD/BuzzAroundHUD.h"
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


