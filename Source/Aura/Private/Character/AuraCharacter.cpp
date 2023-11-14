


#include "Character/AuraCharacter.h"
#include "UI/HUD/AuraHUD.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init for the server
	InitializeAbilityAndAttributeComponents();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init for the client
	InitializeAbilityAndAttributeComponents();
}

void AAuraCharacter::InitializeAbilityAndAttributeComponents()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	if (AuraPlayerState != nullptr)
	{
		AttributeSet = AuraPlayerState->GetAttributeSet();
		AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
		AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);

		if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
		{
			if (AAuraHUD* CurrentHud = Cast<AAuraHUD>(PC->GetHUD()))
			{
				CurrentHud->InitOverlay(PC, AuraPlayerState, AbilitySystemComponent, AttributeSet);
			}
		}
	}
}
