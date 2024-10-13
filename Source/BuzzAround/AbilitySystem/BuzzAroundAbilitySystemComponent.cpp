// Fill out your copyright notice in the Description page of Project Settings.


#include "BuzzAroundAbilitySystemComponent.h"
#include "Abilities/BuzzAroundGameplayAbility.h"

void UBuzzAroundAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UBuzzAroundAbilitySystemComponent::EffectApplied_Implementation);
}

void UBuzzAroundAbilitySystemComponent::AddCharacterAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (TSubclassOf<UGameplayAbility> Ability : StartupAbilities)
	{
		//Need to create spec first, as in GameplayEffects
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		//Cast to AuraGameplayAbility in order to access the startup tag. This is only for start up, if changed during runtime we cannot use varaibles from AuraGameplayAbility
		//NB!!! The cast MUST be from the AbilitySpec, e.g. AbilitySpec.Ability will work, passing only Ability from the loop WILL NOT
		if (const UBuzzAroundGameplayAbility* AuraAbility = Cast<UBuzzAroundGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag);
			//Then you grant the ability:
			GiveAbility(AbilitySpec);
		}
	}
}


void UBuzzAroundAbilitySystemComponent::EffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                                     const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}

