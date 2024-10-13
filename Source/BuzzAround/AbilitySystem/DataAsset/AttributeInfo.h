// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"


USTRUCT(Blueprintable)
struct FBuzzAroundAttributeInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription;

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};
/**
 * 
 */
UCLASS()
class BUZZAROUND_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FBuzzAroundAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FBuzzAroundAttributeInfo> AttributeInformation;
};
