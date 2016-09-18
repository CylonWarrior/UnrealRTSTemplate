// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "RTSHUD.h"


ARTSHUD::ARTSHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	isDrawingSelectionBox_{false},
	selectionBoxFillColor_{ 0.0f,0.0f,1.0f,0.25f },
	borderThickness_{2.0f},
	selectionBoxBorderColor_{0.0f,0.0f,1.0f,1.0f}
{

}
void ARTSHUD::DrawHUD()
{
	Super::DrawHUD();

	if (isDrawingSelectionBox_)
	{
		GetOwningPlayerController()->GetMousePosition(currentMousePosition_.X, currentMousePosition_.Y);
		//InternalBox
		DrawRect(selectionBoxFillColor_,
			initialMousePosition_.X, 
			initialMousePosition_.Y, 
			currentMousePosition_.X - initialMousePosition_.X, 
			currentMousePosition_.Y - initialMousePosition_.Y);

		//top left to top right
		DrawLine(initialMousePosition_.X,
			initialMousePosition_.Y,
			currentMousePosition_.X,
			initialMousePosition_.Y,
			selectionBoxBorderColor_,
			borderThickness_);

		//top right to bottom right
		DrawLine(currentMousePosition_.X,
			initialMousePosition_.Y,
			currentMousePosition_.X,
			currentMousePosition_.Y,
			selectionBoxBorderColor_,
			borderThickness_);

		//bottom right to bottom left
		DrawLine(currentMousePosition_.X,
			currentMousePosition_.Y,
			initialMousePosition_.X,
			currentMousePosition_.Y,
			selectionBoxBorderColor_,
			borderThickness_);

		//bottom left to top left
		DrawLine(initialMousePosition_.X,
			currentMousePosition_.Y,
			initialMousePosition_.X,
			initialMousePosition_.Y,
			selectionBoxBorderColor_,
			borderThickness_);
	}
}

void ARTSHUD::BeginDrawSelectionBox(const FVector2D& initialMousePosition)
{
	isDrawingSelectionBox_ = true;
	initialMousePosition_ = initialMousePosition;
}

void ARTSHUD::StopDrawSelectionBox()
{
	isDrawingSelectionBox_ = false;
}
