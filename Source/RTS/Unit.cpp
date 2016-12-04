// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "Unit.h"
#include "UnitAIController.h"

// Sets default values
AUnit::AUnit()
	: UnitController(nullptr)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(RTSLog, Log, TEXT("Unit BeginPlay"));
	if (UnitController == nullptr)
	{
		UE_LOG(RTSLog, Log, TEXT("Controller is null"));
	}
	if (Controller == nullptr)
	{
		UE_LOG(RTSLog, Log, TEXT("Controller is null"));
	}
	UnitController = Cast<AUnitAIController>(Controller);
	if (Controller == UnitController)
	{
		UE_LOG(RTSLog, Log, TEXT("Controller is AI Controller"));
	}
	SelectionRing = FindComponentByClass<UDecalComponent>();/*
	auto decals = GetComponentsByClass(TSubclassOf<UDecalComponent>{});
	for (auto& decal : decals)
	{
		if (decal->ComponentHasTag(FName("SelectionRing")))
		{
			SelectionRing = Cast<UDecalComponent>(decal);
			break;
		}
	}*/

}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
//void AUnit::SetupPlayerInputComponent(class UInputComponent* InputComponent)
//{
//	Super::SetupPlayerInputComponent(InputComponent);
//
//
//
//}

void AUnit::Select_Implementation()
{
	SelectionRing->SetHiddenInGame(false);
}

void AUnit::Deselect_Implementation()
{
	SelectionRing->SetHiddenInGame(true);
}

void AUnit::AddHighlight_Implementation()
{
}

void AUnit::RemoveHighlight_Implementation()
{
}

void AUnit::MoveTo_Implementation(const FVector& location, bool isShiftPressed)
{
	UnitController->MoveToLocation(location);
}

void AUnit::Follow_Implementation(const FVector& location, bool isShiftPressed)
{

}

void AUnit::Patrol_Implementation(const FVector& location, bool isShiftPressed)
{

}

void AUnit::Stop_Implementation()
{

}

float AUnit::TakeDamage(float DamageAmount,
	FDamageEvent const & DamageEvent,
	AController * EventInstigator,
	AActor * DamageCauser)
{

	return 0.0f;
}