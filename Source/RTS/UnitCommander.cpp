// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "UnitCommander.h"

// Sets default values
AUnitCommander::AUnitCommander()
{

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a base scenecomponent at the root
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//Setup SpringArm
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-60.0f, 0.0f, 0.0f));
	CameraSpringArm->TargetArmLength = 400.0f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 3.0f;
	CameraSpringArm->bDoCollisionTest = false;
	//Setup Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AUnitCommander::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitCommander::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (currentZoomState == ZoomState::ZoomIn)
	{
		ZoomTarget = CurrentZoomLevel + ZoomIncrement;         //Zoom in over half a second
		ZoomTarget = FMath::Clamp<float>(ZoomTarget, 0.0f, 1.0f);
		currentZoomState = ZoomState::None;
	}
	else if (currentZoomState == ZoomState::ZoomOut)
	{
		ZoomTarget = CurrentZoomLevel - ZoomIncrement;        //Zoom out over a quarter of a second
		ZoomTarget = FMath::Clamp<float>(ZoomTarget, 0.0f, 1.0f);
		currentZoomState = ZoomState::None;
	}
	if (!FMath::IsNearlyEqual(CurrentZoomLevel, ZoomTarget))
	{
		CurrentZoomLevel = FMath::Lerp(CurrentZoomLevel, ZoomTarget, ZoomSpeed * DeltaTime);
	}
	//Blend our camera's FOV and our SpringArm's length based on ZoomFactor
	Camera->FieldOfView = FMath::Lerp<float>(MaxFieldOfView, MinFieldOfView, CurrentZoomLevel);
	CameraSpringArm->TargetArmLength = FMath::Lerp<float>(MaxZoomDistance, MinZoomDistance, CurrentZoomLevel);
	//Adjust Rotation based off zoom level
	FRotator NewSpringArmRotation = CameraSpringArm->GetComponentRotation();
	//NewSpringArmRotation.Pitch = FMath::Lerp<float>(-70.0f, -15.0f, CurrentZoomLevel);
	NewSpringArmRotation.Pitch = cameraPitchAngle->GetFloatValue(CurrentZoomLevel);	

	CameraSpringArm->SetWorldRotation(NewSpringArmRotation);

	float MovementMultiplier = CameraSpringArm->TargetArmLength / MinZoomDistance;
	//Movement
	if (!MovementInput.IsZero())
	{
		//Scale our movement input axis values by 100 units per second
		MovementInput = MovementInput.GetSafeNormal() * 100.0f;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * MovementInput.Y * MovementSpeed * MovementMultiplier * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.X * MovementSpeed * MovementMultiplier * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void AUnitCommander::SetupPlayerInputComponent(UInputComponent* uInputComponent)
{
	Super::SetupPlayerInputComponent(uInputComponent);

	//Hook up events for "ZoomIn"

	//Hook up every-frame handling for our four axes
	uInputComponent->BindAction("ZoomIn", EInputEvent::IE_Pressed, this, &AUnitCommander::ZoomIn);
	uInputComponent->BindAction("ZoomOut", EInputEvent::IE_Pressed, this, &AUnitCommander::ZoomOut);
	uInputComponent->BindAxis("MoveForward", this, &AUnitCommander::MoveForward);
	uInputComponent->BindAxis("MoveRight", this, &AUnitCommander::MoveRight);
	uInputComponent->BindAxis("CameraPitch", this, &AUnitCommander::PitchCamera);
	uInputComponent->BindAxis("CameraYaw", this, &AUnitCommander::YawCamera);

}

void AUnitCommander::MoveForward(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void AUnitCommander::MoveRight(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void AUnitCommander::PitchCamera(float AxisValue)
{

}

void AUnitCommander::YawCamera(float AxisValue)
{

}

void AUnitCommander::ZoomIn()
{
	currentZoomState = ZoomState::ZoomIn;
}

void AUnitCommander::ZoomOut()
{
	currentZoomState = ZoomState::ZoomOut;
}
