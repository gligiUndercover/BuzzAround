// Fill out your copyright notice in the Description page of Project Settings.

#include "BuzzAroundAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UBuzzAroundAttributeSet::UBuzzAroundAttributeSet()
{
	// Health = 3.f;
}

void UBuzzAroundAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UBuzzAroundAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBuzzAroundAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UBuzzAroundAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}

void UBuzzAroundAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties EffectProps;
	SetEffectProperties(Data, EffectProps);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
}

void UBuzzAroundAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,
                                                  FEffectProperties& EffectProps) const
{
	//Source = cause of the effect, Target = target of the effect (owner of this)
	EffectProps.EffectCtxHandle = Data.EffectSpec.GetContext();
	EffectProps.SourceASC = EffectProps.EffectCtxHandle.GetOriginalInstigatorAbilitySystemComponent();
	
	if (IsValid(EffectProps.SourceASC) && EffectProps.SourceASC->AbilityActorInfo.IsValid() && EffectProps.SourceASC->AbilityActorInfo->AvatarActor.Get())
	{
		EffectProps.SourceAvatarActor = EffectProps.SourceASC->AbilityActorInfo->AvatarActor.Get();
		EffectProps.SourceController = EffectProps.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (EffectProps.SourceController == nullptr && EffectProps.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(EffectProps.SourceAvatarActor))
			{
				EffectProps.SourceController = Pawn->GetController();
			}
		}
		if (EffectProps.SourceController)
		{
			EffectProps.SourceCharacter = Cast<ACharacter>(EffectProps.SourceController->GetPawn());
		}
	}

	const auto AbilityActorInfoFromData = Data.Target.AbilityActorInfo;
	if (AbilityActorInfoFromData.IsValid() && AbilityActorInfoFromData->AvatarActor.Get())
	{
		EffectProps.TargetAvatarActor = AbilityActorInfoFromData->AvatarActor.Get();
		EffectProps.TargetController = AbilityActorInfoFromData->PlayerController.Get();
		EffectProps.TargetCharacter = Cast<ACharacter>(EffectProps.TargetAvatarActor);
		EffectProps.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProps.TargetAvatarActor);
	}
}

void UBuzzAroundAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBuzzAroundAttributeSet, Health, OldHealth);
}

void UBuzzAroundAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBuzzAroundAttributeSet, MaxHealth, OldMaxHealth);
}
