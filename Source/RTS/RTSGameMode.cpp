// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "RTSGameMode.h"

#include "RTSPlayerController.h"
#include "RTSGameState.h"
#include "RTSPlayerState.h"
#include "UnitCommander.h"
#include "RTSHUD.h"

ARTSGameMode::ARTSGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = ARTSPlayerController::StaticClass();
	DefaultPawnClass = AUnitCommander::StaticClass();
	GameStateClass = ARTSGameState::StaticClass();
	PlayerStateClass = ARTSPlayerState::StaticClass();
	HUDClass = ARTSHUD::StaticClass();
}
