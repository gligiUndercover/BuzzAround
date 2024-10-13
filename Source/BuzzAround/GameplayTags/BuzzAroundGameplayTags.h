#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Singleton containing native GameplayTags
 */
struct FBuzzAroundGameplayTags
{
public:
	static const FBuzzAroundGameplayTags& GetBuzzAroundGameplayTags()
	{
		return GameplayTags;
	}
	
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_MaxHealth;
	FGameplayTag Attributes_Health;

private:
	static FBuzzAroundGameplayTags GameplayTags;
};
