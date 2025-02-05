// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class UParticleSystem;

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootSceneComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh = nullptr;

	//UPROPERTY(VisibleAnywhere)
	//USceneComponent* SpawnFireTransform = nullptr;

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	UParticleSystem* FireParticleSystem = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	FName FireParticleSocketName = FName();
	
	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	UParticleSystem* HitParticleSystem = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float FireRange = 0.f;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float Damage = 20.f;
};