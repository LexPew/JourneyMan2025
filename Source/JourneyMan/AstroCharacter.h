// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AstroCharacter.generated.h"

UCLASS()
class JOURNEYMAN_API AAstroCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//Hover Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hovering)
	bool bIsHovering{false}; //Whether the player is hovering or not
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hovering)
	bool canHover{false}; //Whether the player is able to hover or not
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hovering)
	float HoverTimer{0.0f}; //How long player has been hovering
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hovering)
	float MaxHoverTime{2.0f}; //Max duration for hovering
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hovering)
	float HoverForce{200.f}; // Constant upward force applied while hovering

	UFUNCTION(BlueprintImplementableEvent, Category = Hovering)
	void OnStartHover();
	
	UFUNCTION(BlueprintImplementableEvent, Category = Hovering)
	void OnStopHover();

	// Sets default values for this character's properties
	AAstroCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable)
	void LaunchToHeight(float WorldHeight, float Speed);
	
	virtual void Jump() override;
	virtual void StopJumping() override;
	virtual void OnLanded() overide;
};
