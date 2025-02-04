#include "AstroCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AAstroCharacter::AAstroCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

}

void AAstroCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AAstroCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsHovering)
    {
        HoverTimer += DeltaTime;

        if (HoverTimer >= MaxHoverTime)
        {
            // Stop hovering when the timer expires
            bIsHovering = false;
            OnStartHover();
            UE_LOG(LogTemp, Warning, TEXT("Stopped Hovering"));
        }
        else
        {
            // Apply constant upward velocity
            FVector NewVelocity = GetCharacterMovement()->Velocity;
            NewVelocity.Z = HoverForce; // Set Z velocity to the constant hover velocity
            GetCharacterMovement()->Velocity = NewVelocity;
        }
    }
}

void AAstroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAstroCharacter::LaunchToHeight(float WorldHeight, float Speed)
{
    float CurrentHeight = GetActorLocation().Z;
    float Gravity = FMath::Abs(GetWorld()->GetGravityZ());
    float HeightDifference = WorldHeight - CurrentHeight;

    // Compute required velocity
    float Velocity = FMath::Sqrt(2 * Gravity * HeightDifference);

    // If falling, compensate for downward velocity
    if (GetVelocity().Z < 0)
    {
        Velocity += FMath::Abs(GetVelocity().Z);
    }

    UE_LOG(LogTemp, Warning, TEXT("Launching with velocity: %f"), Velocity);

    // Apply velocity
    LaunchCharacter(FVector(0, 0, Velocity), false, false);
}

void AAstroCharacter::Jump()
{
    if (!bIsHovering)
    {
        UE_LOG(LogTemp, Warning, TEXT("Jumping"));

        // Check if this is a double jump
        if (JumpCurrentCount > 0 && !canHover && GetCharacterMovement()->IsFalling())
        {
            
            UE_LOG(LogTemp, Warning, TEXT("Starting Hovering"));
            canHover = false;
            bIsHovering = true;
            HoverTimer = 0.0f;
            OnStopHover();
            // Set the constant upward velocity for the hover
            FVector NewVelocity = GetCharacterMovement()->Velocity;
            NewVelocity.Z = HoverForce; // Ignore downward momentum
            GetCharacterMovement()->Velocity = NewVelocity;
        }
        else
        {
            // Perform the first jump
            Super::Jump();
        }
    }
}

void AAstroCharacter::StopJumping()
{
    Super::StopJumping();

    if (bIsHovering)
    {
        bIsHovering = false;
    }
}

void AAstroCharacter::OnLanded()
{
    Super::OnLanded();
    canHover = true;
}