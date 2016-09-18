// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Interface.h"
#include "AttackCommandable.generated.h"

/**
 *
 */
UINTERFACE(BlueprintType)
class RTS_API UAttackCommandable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class RTS_API IAttackCommandable
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Commandable")
		void Attack(AActor* enemyTarget);
};