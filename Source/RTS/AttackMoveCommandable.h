// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Object.h"
#include "Interface.h"

#include "AttackMoveCommandable.generated.h"

/**
 * 
 */
UINTERFACE(BlueprintType)
class RTS_API UAttackMoveCommandable : public UInterface
{ 
	GENERATED_UINTERFACE_BODY()
};

class RTS_API IAttackMoveCommandable
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Commandable")
		void AttackMove(const FVector& location, bool isShiftPressed);
};