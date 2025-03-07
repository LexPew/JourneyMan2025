// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_CombatComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TimerManager.h"
#include "AstroCharacter.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

UAC_CombatComponent::UAC_CombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentAttackIndex = 0;
	bIsAttacking = false;
}


void UAC_CombatComponent::BeginPlay()
{
	Super::BeginPlay();
    
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("CombatComponent: No valid Character owner!"));
		return;
	}

	// Get the Player Controller
	APlayerController* PlayerController = Cast<APlayerController>(OwnerCharacter->GetController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("CombatComponent: No valid PlayerController!"));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CombatComponent: PlayerController is valid!"));
	}

	// Add Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		if (CombatMappingContext)
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding CombatMappingContext to Input Subsystem"));
			InputSubsystem->AddMappingContext(CombatMappingContext, 0);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("CombatComponent: CombatMappingContext is NOT SET!"));
		}
	}
}

void UAC_CombatComponent::StartAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("StartAttack() triggered!"));

	if (bIsAttacking || ComboChain.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot attack: Already attacking or no combo attacks set."));
		return;
	}

	bIsAttacking = true;

	float CurrentTime = GetWorld()->GetTimeSeconds();

	if (CurrentTime - LastCallTime <= ComboChain[CurrentAttackIndex].AttackDuration * 2)
	{
		ExecuteAttack();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Combo reset: Max input delay exceeded"));

		CurrentAttackIndex = 0;
		ExecuteAttack();
	}

	LastCallTime = CurrentTime; // Update the last call time
}

void UAC_CombatComponent::ExecuteAttack()
{
	if (!OwnerCharacter || !OwnerCharacter->GetMesh()) return;

	if (ComboChain.IsValidIndex(CurrentAttackIndex))
	{
		const FAttackData& CurrentAttack = ComboChain[CurrentAttackIndex];
		UE_LOG(LogTemp, Warning, TEXT("Attack %d triggered"), CurrentAttackIndex);

		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &UAC_CombatComponent::ResetAttack, CurrentAttack.AttackDuration, false);
	}
}

void UAC_CombatComponent::ResetAttack()
{
	bIsAttacking = false;

	CurrentAttackIndex = (CurrentAttackIndex + 1) % ComboChain.Num();  // Loop through attacks
}


void UAC_CombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UAC_CombatComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent called!"));

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AttackAction)
		{
			UE_LOG(LogTemp, Warning, TEXT("Binding AttackAction!"));
			EnhancedInput->BindAction(AttackAction, ETriggerEvent::Triggered, this, &UAC_CombatComponent::StartAttack);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("CombatComponent: AttackAction is NOT SET!"));
		}
	}
}
