// Fill out your copyright notice in the Description page of Project Settings.


#include "BuzzAroundProjectileSpell.h"


void UABuzzAroundProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const bool bIsOnServer = HasAuthority(&ActivationInfo);
	if (!bIsOnServer) return;

	//TODO: Spawn points needs to be added here

}
