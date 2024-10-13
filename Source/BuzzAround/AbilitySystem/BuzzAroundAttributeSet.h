// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "BuzzAroundAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


//1. Return type of delegate below = FGameplayAttribute
//2. The name given to the delegate = 
DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeSignature)

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties() {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> SourceASC = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> TargetASC = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> SourceAvatarActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> TargetAvatarActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AController> SourceController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AController> TargetController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ACharacter> SourceCharacter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ACharacter> TargetCharacter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayEffectContextHandle EffectCtxHandle;
};

UCLASS()
class BUZZAROUND_API UBuzzAroundAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBuzzAroundAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	TMap<FGameplayTag, FAttributeSignature> TagsToAttributesMap;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category="Vital stats")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBuzzAroundAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category="Vital stats")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBuzzAroundAttributeSet, MaxHealth);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProps) const;
};
