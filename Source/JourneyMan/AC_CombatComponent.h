// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "InputAction.h"
#include "Components/ActorComponent.h"
#include "AC_CombatComponent.generated.h"

UENUM(BlueprintType)
enum class EHitboxShape : uint8
{
	Box		UMETA(DisplayName = "Box"),
	Sphere  UMETA(DisplayName = "Sphere"),
	Capsule	UMETA(DisplayName = "Capsule")
};

USTRUCT(BlueprintType)
struct FAttackData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	UAnimSequence* AttackAnimation;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float Damage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float AttackDuration = AttackAnimation->GetPlayLength();  // Time before next attack

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	EHitboxShape HitboxShape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	FVector HitboxSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	FVector HitboxOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	FRotator HitboxRotation;

	FAttackData()
		:
			AttackAnimation(nullptr),
			HitboxShape(EHitboxShape::Box),
			HitboxSize(FVector(50.0f,50.0f,50.0f)),
			HitboxOffset(FVector::ZeroVector),
			HitboxRotation(FRotator::ZeroRotator)
		{
		}
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType, Blueprintable )
class JOURNEYMAN_API UAC_CombatComponent : public UActorComponent
{
	GENERATED_BODY()

	float LastCallTime;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	int32 CurrentAttackIndex;
	UPROPERTY(BlueprintReadOnly, Category="Combat")
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
