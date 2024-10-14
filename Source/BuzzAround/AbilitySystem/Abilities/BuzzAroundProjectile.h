// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuzzAroundProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class BUZZAROUND_API ABuzzAroundProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuzzAroundProjectile();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComp
	   ,AActor* OtherActor
	   ,UPrimitiveComponent* OtherComp
	   ,int32 OtherBodyIndex
	   ,bool bFromSweep
	   ,const FHitResult& SweepResult);

private:
	TObjectPtr<USphereComponent> Sphere;
};
