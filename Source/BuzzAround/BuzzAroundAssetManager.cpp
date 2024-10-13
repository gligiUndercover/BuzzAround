// Fill out your copyright notice in the Description page of Project Settings.


#include "BuzzAroundAssetManager.h"

#include "GameplayTags/BuzzAroundGameplayTags.h"

UBuzzAroundAssetManager& UBuzzAroundAssetManager::Get()
{
	check(GEngine);

	return *Cast<UBuzzAroundAssetManager>(GEngine->AssetManager);
}

void UBuzzAroundAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FBuzzAroundGameplayTags::InitializeNativeGameplayTags();
}
