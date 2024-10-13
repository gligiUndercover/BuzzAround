// Fill out your copyright notice in the Description page of Project Settings.


#include "BuzzAroundCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "BuzzAround/AbilitySystem/BuzzAroundAbilitySystemComponent.h"


// Sets default values
ABuzzAroundCharacterBase::ABuzzAroundCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* ABuzzAroundCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ABuzzAroundCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABuzzAroundCharacterBase::InitAbilityActorInfo()
{
}

void ABuzzAroundCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> DefaultAttributes, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultAttributes);
	FGameplayEffectContextHandle EffectCtxHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectCtxHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultAttributes, Level, EffectCtxHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ABuzzAroundCharacterBase::InitAttributes() const
{
	ApplyEffectToSelf(DefaultCharacterAttributes, 1.f);
}

void ABuzzAroundCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;
	UBuzzAroundAbilitySystemComponent* AbilitySystem = Cast<UBuzzAroundAbilitySystemComponent>(AbilitySystemComponent);
	AbilitySystem->AddCharacterAbilities(StartupAbilities);
	
}


