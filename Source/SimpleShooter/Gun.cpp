// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(RootSceneComponent);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void AGun::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("You've been shot!"));
	UGameplayStatics::SpawnEmitterAttached(FireParticleSystem, Mesh, FireParticleSocketName);

	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (!OwnerPawn)
	{
		return;
	}

	FVector OutLocation = FVector::ZeroVector;
	FRotator OutRotation = FRotator::ZeroRotator;
	AController* OwnerController = OwnerPawn->GetController(); 
	
	if (!OwnerController)
	{
		return;
	}

	OwnerController->GetPlayerViewPoint(OutLocation, OutRotation);
	
	FHitResult OutHitResult = FHitResult();
	FVector EndTrace = OutLocation + OutRotation.Vector() * FireRange;
	//UE_LOG(LogTemp, Warning, TEXT("OutRotation.Vector: %s"), *OutRotation.Vector().ToString());
	bool HasHit = GetWorld()->LineTraceSingleByChannel(OutHitResult, OutLocation, EndTrace, ECollisionChannel::ECC_GameTraceChannel1);

	if (!HasHit)
	{
		return;
	}

	FVector FireDirection = -OutRotation.Vector();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticleSystem, OutHitResult.Location, FireDirection.Rotation());

	DrawDebugLine(GetWorld(), OutLocation, EndTrace, FColor::Red, true);
	DrawDebugPoint(GetWorld(), OutHitResult.Location, 20.f, FColor::Red, true);
	//DrawDebugCamera(GetWorld(), OutLocation, OutRotation, 90.f, 1.f, FColor::Red, true);

	AActor* HitActor = OutHitResult.GetActor();
	if (!HitActor)
	{
		return;
	}

	FPointDamageEvent DamageEvent = FPointDamageEvent(Damage, OutHitResult, FireDirection, nullptr);
	HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}