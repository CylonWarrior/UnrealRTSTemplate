// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "UnitCommander.generated.h"

UCLASS()
class RTS_API AUnitCommander : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Camera Controls")
		USpringArmComponent* CameraSpringArm;
	UPROPERTY(EditAnywhere, Category = "Camera Controls", meta = (ClampMin = 100.0f, ClampMax = 800.0f, UIMin = 100.0f, UIMax = 800.0f))
		float MinZoomDistance = 500.0f;
	UPROPERTY(EditAnywhere, Category = "Camera Controls", meta = (ClampMin = 450.0f, ClampMax = 2000.0f, UIMin = 450.0f, UIMax = 2000.0f))
		float MaxZoomDistance = 500.0f;
	UPROPERTY(EditAnywhere, Category = "Camera Controls", meta = (ClampMin = 30.0f, ClampMax = 70.0f, UIMin = 30.0f, UIMax = 70.0f))
		float MinFieldOfView = 60.0f;
	UPROPERTY(EditAnywhere, Category = "Camera Controls", meta = (ClampMin = 80.0, ClampMax = 120.0f, UIMin = 80.0, UIMax = 120.0f))
		float MaxFieldOfView = 90.0f;
	UPROPERTY(EditAnywhere, Category = "Camera Controls", meta = (ClampMin = 0.01f, ClampMax = 0.2f, UIMin = 0.01f, UIMax = 0.2f))
		float ZoomIncrement = 0.1f;
	UPROPERTY(EditAnywhere, Category = "Camera Controls", meta = (ClampMin = 2.0f, ClampMax = 10.0f, UIMin = 1.0f, UIMax = 10.0f))
		float ZoomSpeed = 5.0f;
	UPROPERTY(EditAnywhere, Category = "Camera Controls", meta = (ClampMin = 1.0f, ClampMax = 10.0f, UIMin = 1.0f, UIMax = 10.0f))
		float MovementSpeed = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Camera Controls", meta = (ClampMin = 0.0f, ClampMax = 1.0f, UIMin = 0.0f, UIMax = 1.0f))
	float CurrentZoomLevel = 0.25f;
	UPROPERTY(EditAnywhere, Category = "Camera Controls")
	UCurveFloat* cameraPitchAngle;
	float ZoomTarget = 0.25f;
	enum class ZoomState
	{
		None,
		ZoomIn,
		ZoomOut
	};
	UCameraComponent* Camera;
	FVector2D MovementInput; //Movement
	FVector2D CameraInput; //Pitch & yaw
	ZoomState currentZoomState;
public:
	// Sets default values for this pawn's properties
	AUnitCommander();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void ZoomIn();
	void ZoomOut();
	
};
