// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "RTSHUD.generated.h"

/**
 *
 */
UCLASS()
class RTS_API ARTSHUD : public AHUD
{
	GENERATED_BODY()
protected:
	bool isDrawingSelectionBox_;
	FVector2D initialMousePosition_;
	FVector2D currentMousePosition_;
	UPROPERTY(EditAnywhere, Category = "Selection Box")
		FLinearColor selectionBoxBorderColor_;
	UPROPERTY(EditAnywhere, Category = "Selection Box")
		float borderThickness_;
	UPROPERTY(EditAnywhere, Category = "Selection Box")
		FLinearColor selectionBoxFillColor_;
public:
	ARTSHUD(const FObjectInitializer& ObjectInitializer);
	virtual void DrawHUD() override;

	void BeginDrawSelectionBox(const FVector2D& initialMousePosition);
	void StopDrawSelectionBox();
};
