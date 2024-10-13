// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffect.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BuzzAroundCharacterBase.generated.h"

class UAbilitySystemComponent;

UCLASS()
class BUZZAROUND_API ABuzzAroundCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABuzzAroundCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect>  DefaultCharacterAttributes;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> DefaultAttributes, float Level) const;
	void InitAttributes() const;

	void AddCharacterAbilities(); //TODO: This function has the same name as in AbilitySystemComponent

private:

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
