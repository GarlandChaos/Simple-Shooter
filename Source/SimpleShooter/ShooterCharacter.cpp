// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpFrameRateIndependent", this, &AShooterCharacter::LookUpFrameRateIndependent);
	PlayerInputComponent->BindAxis("Strafe", this, &AShooterCharacter::Strafe);
	PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookRightFrameRateIndependent", this, &AShooterCharacter::LookRightFrameRateIndependent);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}

void AShooterCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AShooterCharacter::Strafe(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AShooterCharacter::LookUpFrameRateIndependent(float Value)
{
	AddControllerPitchInput(Value * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightFrameRateIndependent(float Value)
{
	AddControllerYawInput(Value * RotationRate * GetWorld()->GetDeltaSeconds());
}