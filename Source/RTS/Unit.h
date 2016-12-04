// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MoveCommandable.h"
#include "Selectable.h"
#include "StopCommandable.h"

#include "Unit.generated.h"

UCLASS()
class RTS_API AUnit : public ACharacter, public ISelectable, public IMoveCommandable, public IStopCommandable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Unit Stats")
		float Health;

	UPROPERTY(EditAnywhere, Category = "Unit Selection")
		UDecalComponent* SelectionRing;

	class AUnitAIController* UnitController;
public:
	// Sets default values for this character's properties
	AUnit();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selectable")
		void Select();
	virtual void Select_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selectable")
		void Deselect();
	virtual void Deselect_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selectable")
		void AddHighlight();
	virtual void AddHighlight_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selectable")
		void RemoveHighlight();
	virtual void RemoveHighlight_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Commandable")
		void MoveTo(const FVector& location, bool isShiftPressed);
	virtual void MoveTo_Implementation(const FVector& location, bool isShiftPressed) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Commandable")
		void Follow(const FVector& location, bool isShiftPressed);
	virtual void Follow_Implementation(const FVector& location, bool isShiftPressed) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Commandable")
		void Patrol(const FVector& location, bool isShiftPressed);
	virtual void Patrol_Implementation(const FVector& location, bool isShiftPressed) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Commandable")
		void Stop();
	virtual void Stop_Implementation() override;

	virtual float TakeDamage(float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		AController * EventInstigator,
		AActor * DamageCauser) override;
};
