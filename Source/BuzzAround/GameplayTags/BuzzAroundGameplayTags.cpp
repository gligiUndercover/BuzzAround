#include "BuzzAroundGameplayTags.h"
#include "GameplayTagsManager.h"

FBuzzAroundGameplayTags FBuzzAroundGameplayTags::GameplayTags;

void FBuzzAroundGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.MaxHealth"), FString("MaxHealth"));
	GameplayTags.Attributes_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Health"), FString("Health"));
}
