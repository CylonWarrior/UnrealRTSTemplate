// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "UnitAIController.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API AUnitAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

};
