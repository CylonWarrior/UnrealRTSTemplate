// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "UnitAIController.h"


void AUnitAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(RTSLog, Log, TEXT("AIController BeginPlay"));
}
