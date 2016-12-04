// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

/**
 *
 */
UCLASS()
class RTS_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	bool isLeftClickDown;
	bool isRightClickDown;
	FVector2D initialMousePosition;
	//FVector2D currentMousePosition;
	class ARTSHUD* RTSHUD;
	TArray<AActor*> currentSelection;
public:
	ARTSPlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void OnLeftClickPressed();
	virtual void OnLeftClickHeld();
	virtual void OnLeftClickReleased();
	virtual void OnRightClickPressed();
	virtual void OnRightClickHeld();
	virtual void OnRightClickReleased();
};
