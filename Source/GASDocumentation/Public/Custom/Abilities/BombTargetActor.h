// Copyright 2020 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"

#include "Abilities/GameplayAbilityTargetActor.h"
#include "BombTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class GASDOCUMENTATION_API ABombTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	ABombTargetActor();

	virtual void StartTargeting(UGameplayAbility* InAbility) override;

	virtual void ConfirmTargetingAndContinue() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	class UDecalComponent* decal;


protected:
	bool IsStartTargeting;

	FVector2D aimSightsPosition;
	FVector2D screenSize;

	class AGDPlayerController* playerController;
	class AGDHeroCharacter* character;
	class UGDHUDWidget* UIWidget;

	
};
