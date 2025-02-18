// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "InputAction.h"
#include "Components/ActorComponent.h"
#include "AC_CombatComponent.generated.h"


USTRUCT(BlueprintType)
struct FAttackData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	UAnimMontage* AttackAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float Damage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float AttackDuration = 0.5f;  // Time before next attack

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType, Blueprintable )
class JOURNEYMAN_API UAC_CombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAC_CombatComponent();

protected:
	virtual void BeginPlay() override;

	// Input Handling
	UFUNCTION(BlueprintCallable)
	void StartAttack();

	// Attack Handling
	void ExecuteAttack();
	void ResetAttack();

	// Reference to Owner
	ACharacter* OwnerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	TArray<FAttackData> ComboChain;  // List of attacks in combo

	int32 CurrentAttackIndex;
	bool bIsAttacking;
	FTimerHandle AttackTimerHandle;

	//Input 
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* AttackAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* CombatMappingContext;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

		
};
