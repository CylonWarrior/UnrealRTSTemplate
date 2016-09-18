// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Interface.h"
#include "MoveCommandable.generated.h"

/**
 * 
 */
UINTERFACE(BlueprintType)
class RTS_API UMoveCommandable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class RTS_API IMoveCommandable
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Commandable")
		void MoveTo(const FVector& location, bool isShiftPressed);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Commandable")
		void Follow(const FVector& location, bool isShiftPressed);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Commandable")
		void Patrol(const FVector& location, bool isShiftPressed);
};