// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "RTSPlayerController.h"
#include "Selectable.h"
#include "RTSHUD.h"



ARTSPlayerController::ARTSPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	isLeftClickDown{ false },
	isRightClickDown{ true }
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}


void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftClick", EInputEvent::IE_Pressed, this, &ARTSPlayerController::OnLeftClickPressed);
	InputComponent->BindAction("LeftClick", EInputEvent::IE_Released, this, &ARTSPlayerController::OnLeftClickReleased);
	InputComponent->BindAction("RightClick", EInputEvent::IE_Pressed, this, &ARTSPlayerController::OnRightClickPressed);
	InputComponent->BindAction("RightClick", EInputEvent::IE_Released, this, &ARTSPlayerController::OnRightClickReleased);
}

void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	RTSHUD = Cast<ARTSHUD>(MyHUD);
	if (RTSHUD == nullptr)
	{
		UE_LOG(RTSLog, Log, TEXT("Casting HUD in begin play doesnt work"));
	}
}

void ARTSPlayerController::Tick(float DeltaSeconds)
{
	if (isLeftClickDown)
	{
		OnLeftClickHeld();
	}
	if (isRightClickDown)
	{
		OnRightClickHeld();
	}
}



void ARTSPlayerController::OnLeftClickPressed()
{
	isLeftClickDown = true;
	if (!GetMousePosition(initialMousePosition.X, initialMousePosition.Y))
	{
		//isLeftClickDown = false;
	}
	RTSHUD->BeginDrawSelectionBox(initialMousePosition);
}

void ARTSPlayerController::OnLeftClickHeld()
{

	//GetMousePosition(currentMousePosition.X, currentMousePosition.Y);
	UE_LOG(RTSLog, Log, TEXT("On Left Click Held Running"));
	//MyHUD->DrawRect(FLinearColor::Blue, initialMousePosition.X, initialMousePosition.Y, currentMousePosition.X - initialMousePosition.X, currentMousePosition.Y - initialMousePosition.Y);
}

void ARTSPlayerController::OnLeftClickReleased()
{
	isLeftClickDown = false;
	RTSHUD->StopDrawSelectionBox();
	//Collect Selected Units
	FVector2D currentMousePosition;
	GetMousePosition(currentMousePosition.X, currentMousePosition.Y);
	TArray<AActor*> selectableActors;
	
	UGameplayStatics::GetAllActorsWithInterface(GetWorld())
}




void ARTSPlayerController::OnRightClickPressed()
{
	isRightClickDown = true;
}

void ARTSPlayerController::OnRightClickHeld()
{

}

void ARTSPlayerController::OnRightClickReleased()
{
	isRightClickDown = true;
}
