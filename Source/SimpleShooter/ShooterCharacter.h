// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void Strafe(float Value);

	// Used for gamepad because read values are not consistent for each different fps
	void LookUpFrameRateIndependent(float Value);
	void LookRightFrameRateIndependent(float Value);

	UPROPERTY(EditAnywhere, Category = "Frame Rate Independent Rotation")
	float RotationRate = 10.f;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TSubclassOf<class AGun> GunClass = nullptr;

	UPROPERTY()
	AGun* Gun = nullptr;
};