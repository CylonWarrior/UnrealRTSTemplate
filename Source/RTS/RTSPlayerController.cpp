// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "RTSPlayerController.h"
#include "Selectable.h"
#include "MoveCommandable.h"
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
	UObject* pointerToAnyUObject = nullptr;

	//Clear out current Selection
	for (auto& actor : currentSelection)
	{
		ISelectable::Execute_Deselect(Cast<UObject>(actor));
	}
	currentSelection.Empty();

	//GetMousePosition(currentMousePosition.X, currentMousePosition.Y);
	UE_LOG(RTSLog, Log, TEXT("On Left Click Held Running"));
	//MyHUD->DrawRect(FLinearColor::Blue, initialMousePosition.X, initialMousePosition.Y, currentMousePosition.X - initialMousePosition.X, currentMousePosition.Y - initialMousePosition.Y);
	FVector2D currentMousePosition;
	GetMousePosition(currentMousePosition.X, currentMousePosition.Y);

	/*float lowerX = initialMousePosition.X < currentMousePosition.X ? initialMousePosition.X : currentMousePosition.X;
	float upperX = initialMousePosition.X > currentMousePosition.X ? initialMousePosition.X : currentMousePosition.X;

	float lowerY = initialMousePosition.Y < currentMousePosition.Y ? initialMousePosition.Y : currentMousePosition.Y;
	float upperY = initialMousePosition.Y > currentMousePosition.Y ? initialMousePosition.Y : currentMousePosition.Y;*/

	FBox2D box;
	box += initialMousePosition;
	box += currentMousePosition;


	TArray<AActor*> selectableActors;

	FVector2D screenPos;
	for (TActorIterator<AActor> Itr(GetWorld()); Itr; ++Itr)
	{
		if (!Itr->GetClass()->ImplementsInterface(USelectable::StaticClass()))
		{
			continue;
		}
		FVector worldPos = Itr->GetActorLocation();
		if (!ProjectWorldLocationToScreen(worldPos, screenPos))
		{
			continue;
		}
		if (box.IsInside(screenPos))
		{
			ISelectable::Execute_Select(Cast<UObject>(*Itr));
			currentSelection.Add(*Itr);
		}
	}

	/*for (auto& actor : selectableActors)
	{
		ISelectable* selectable = Cast<ISelectable>(actor);
		if (selectable)
		{
			FVector worldPos = actor->GetActorLocation();
			if (!ProjectWorldLocationToScreen(worldPos, screenPos))
			{
				continue;
			}
			if (box.IsInside(screenPos))
			{

			}
		}
	}*/


	//for (auto& actor : selectableActors)
	//{
	//	ISelectable* selectable = Cast<ISelectable>(actor);
	//	FVector worldPos = actor->GetActorLocation();
	//	if (selectable)
	//	{
	//		FVector2D screenPos;
	//		if (!ProjectWorldLocationToScreen(worldPos, screenPos))
	//		{
	//			continue;
	//		}
	//		if (screenPos.X > lowerX && screenPos.X < upperX &&
	//			screenPos.Y > lowerY && screenPos.Y < upperY)
	//		{
	//			ISelectable::Execute_AddHighlight(pointerToAnyUObject);
	//			currentSelection.Add(actor);
	//		}
	//	}
	//}


}

void ARTSPlayerController::OnLeftClickReleased()
{
	isLeftClickDown = false;
	RTSHUD->StopDrawSelectionBox();
	//Collect Selected Units
	
	

	//TSubclassOf<USelectable> selectable;

	//UGameplayStatics::GetAllActorsWithInterface(GetWorld(), selectable, selectableActors);


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
	FVector2D currentMousePosition;
	GetMousePosition(currentMousePosition.X, currentMousePosition.Y);

	FVector position;
	FVector direction;
	DeprojectScreenPositionToWorld(currentMousePosition.X, currentMousePosition.Y, position, direction);

	float distance = 4000.f;
	FHitResult result;
	GetWorld()->LineTraceSingleByObjectType(result, position, position + direction * distance, ECC_WorldStatic);

	for (auto& selectable : currentSelection)
	{
		if (selectable->GetClass()->ImplementsInterface(UMoveCommandable::StaticClass()))
		{
			IMoveCommandable::Execute_MoveTo(Cast<UObject>(selectable), result.Location, false);
		}
	}
}
