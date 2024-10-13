// Fill out your copyright notice in the Description page of Project Settings.


#include "BuzzAroundPlayerState.h"
#include "BuzzAround/AbilitySystem/BuzzAroundAttributeSet.h"


ABuzzAroundPlayerState::ABuzzAroundPlayerState()
{
	NetUpdateFrequency = 100.f; //How fast the server updates clients in multiplayer env

	AbilitySystemComponent = CreateDefaultSubobject<UBuzzAroundAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UBuzzAroundAttributeSet>("AttributeSet");
}

void ABuzzAroundPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//NO levels as of yet so nothing to replicate, if char levels are included an integer variable should be initialized in the h player state AND also a OnRep_% callback function
	// DOREPLIFETIME_CONDITION_NOTIFY(ABuzzAroundPlayerState, CharacterLevel, COND_None, REPNOTIFY_Always);
}

UAbilitySystemComponent* ABuzzAroundPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
