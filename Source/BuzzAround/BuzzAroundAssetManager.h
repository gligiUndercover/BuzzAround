// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "BuzzAroundAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class BUZZAROUND_API UBuzzAroundAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static UBuzzAroundAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
