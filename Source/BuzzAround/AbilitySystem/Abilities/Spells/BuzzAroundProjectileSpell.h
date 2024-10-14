// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuzzAround/AbilitySystem/Abilities/BuzzAroundGameplayAbility.h"
#include "BuzzAround/AbilitySystem/Abilities/BuzzAroundProjectile.h"
#include "BuzzAroundProjectileSpell.generated.h"

struct FGameplayEventData;

UCLASS()
class BUZZAROUND_API UABuzzAroundProjectileSpell : public UBuzzAroundGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(
			const FGameplayAbilitySpecHandle Handle
		   ,const FGameplayAbilityActorInfo* ActorInfo
		   ,const FGameplayAbilityActivationInfo ActivationInfo
		   ,const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABuzzAroundProjectile> ProjectileClass;
};
