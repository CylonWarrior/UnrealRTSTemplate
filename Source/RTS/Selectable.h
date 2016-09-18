// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Interface.h"
#include "Selectable.generated.h"

/**
 *
 */
UINTERFACE(BlueprintType)
class RTS_API USelectable : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class RTS_API ISelectable
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selectable")
		void Select();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selectable")
		void Deselect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selectable")
		void AddHighlight();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selectable")
		void RemoveHighlight();
};