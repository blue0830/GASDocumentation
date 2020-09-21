// Copyright 2020 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "Custom/Abilities/Bomb.h"
#include "Custom/Abilities/BombTargetActor.h"
#include "Custom/Abilities/GEBombDamage.h"
#include "Custom/Abilities/GEBombFire.h"
#include "Characters/Abilities/GDGameplayAbility.h"
#include "Characters/Heroes/GDHeroCharacter.h"
#include "GDGABomb.generated.h"

/**
 * 
 */
UCLASS()
class GASDOCUMENTATION_API UGDGABomb : public UGDGameplayAbility
{
	GENERATED_BODY()

public:
	UGDGABomb();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	void UpdateCamera();

	void SetTargetLocation();

	UFUNCTION()
	void OnProcess(const FGameplayAbilityTargetDataHandle& Data);

	UFUNCTION()
	void OnComplete(const FGameplayAbilityTargetDataHandle& Data);

	UFUNCTION()
	void OnCancel(const FGameplayAbilityTargetDataHandle& Data);

public:
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	TSubclassOf<ABombTargetActor> targetActorClass;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	float chooseRange;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	class UAbilityTask_WaitTargetData* targetTask;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	float bombDamage;

	ABomb* bomb;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	AGDHeroCharacter* owner;

	class UAbilityTask_WaitTargetData* waitTargetDataTask;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	TSubclassOf<UGEBombDamage> geBombDamageClass;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	TSubclassOf<UGEBombFire> geBombFireClass;

};
