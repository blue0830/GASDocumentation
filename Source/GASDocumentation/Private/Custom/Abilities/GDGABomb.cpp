// Copyright 2020 Dan Kestranek.


#include "Custom/Abilities/GDGABomb.h"
#include "Player/GDPlayerState.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "AbilitySystemComponent.h"
#include "Custom/Abilities/GEBombCost.h"
#include "Custom/Abilities/GEBombCooldown.h"

UGDGABomb::UGDGABomb() {

	AbilityID = EGDAbilityInputID::Bomb;
	AbilityInputID = EGDAbilityInputID::Bomb;
	
}

void UGDGABomb::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//WaitTargetData()
	AActor* actor = GetAvatarActorFromActorInfo();
	owner = Cast<AGDHeroCharacter>(actor);
	AActor* owningActor = GetOwningActorFromActorInfo();
	AGDPlayerState* playerState = Cast<AGDPlayerState>(owningActor);
	playerState->ShowAbilityConfirmCancelText(true);



	UpdateCamera();
	//BreakGameplayAbilityTargetingLocationInfo
	//BreakGameplayAbilityTargetingLocationInfo
	//MakeTargetLocationInfoFromOwnerActor()

	SetTargetLocation();
	
}

void UGDGABomb::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	USpringArmComponent* cameraArm = owner->GetCameraBoom();
	cameraArm->SetRelativeLocation(owner->GetStartingCameraBoomLocation());
	AActor* actor = GetOwningActorFromActorInfo();
	AGDPlayerState* playerState = Cast<AGDPlayerState>(actor);
	playerState->ShowAbilityConfirmCancelText(false);
}

void UGDGABomb::UpdateCamera()
{
	FVector startPos = owner->GetStartingCameraBoomLocation();
	startPos.Z += 100;
	owner->GetCameraBoom()->SetRelativeLocation(startPos);
}

void UGDGABomb::SetTargetLocation()
{
	FGameplayAbilityTargetingLocationInfo locationInfo = MakeTargetLocationInfoFromOwnerActor();
	FVector forward = owner->GetActorForwardVector();
	forward.X *= 200;
	locationInfo.LiteralTransform.SetLocation(forward);
	
	waitTargetDataTask = UAbilityTask_WaitTargetData::WaitTargetData(this, FName("WaitLocationData"), EGameplayTargetingConfirmation::UserConfirmed, /*targetActorClass*/ABombTargetActor::StaticClass());

	AGameplayAbilityTargetActor* targetActor;
	waitTargetDataTask->BeginSpawningActor(this, ABombTargetActor::StaticClass(), targetActor);
	waitTargetDataTask->FinishSpawningActor(this, targetActor);
	//targetActor->SetActorRelativeLocation(forward);
	//bombTargetActor->delegate
	


	waitTargetDataTask->ValidData.AddDynamic(this, &UGDGABomb::OnComplete);
	waitTargetDataTask->Cancelled.AddDynamic(this, &UGDGABomb::OnCancel);
	waitTargetDataTask->ReadyForActivation();
	
}

void UGDGABomb::OnProcess(const FGameplayAbilityTargetDataHandle& Data)
{
}

void UGDGABomb::OnComplete(const FGameplayAbilityTargetDataHandle& Data)
{
	bool isSuccess = CommitAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo);
	if (!isSuccess || !HasAuthority(&CurrentActivationInfo)) {
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,true,true);
		return;
	}

	FGameplayEffectSpecHandle costEffectHandle = MakeOutgoingGameplayEffectSpec(UGEBombCost::StaticClass(), GetAbilityLevel());
	FGameplayEffectSpecHandle cooldownEffectHandle = MakeOutgoingGameplayEffectSpec(UGEBombCooldown::StaticClass(), GetAbilityLevel());

	owner->GetAbilitySystemComponent()->BP_ApplyGameplayEffectSpecToSelf(costEffectHandle);
	owner->GetAbilitySystemComponent()->BP_ApplyGameplayEffectSpecToSelf(cooldownEffectHandle);

	FGameplayEffectSpecHandle damageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(UGEBombDamage::StaticClass(), GetAbilityLevel());
	damageEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")),100);
	if (Data.IsValid(0)) {
		const FGameplayAbilityTargetData* data = Data.Get(0);
		const FGameplayAbilityTargetData_LocationInfo* locationInfo = (FGameplayAbilityTargetData_LocationInfo *)(data);
		FVector pos = locationInfo->TargetLocation.LiteralTransform.GetLocation();
		pos.Z = 150;
		
		bomb = GetWorld()->SpawnActor<ABomb>(/*ABomb::StaticClass()*/bombClass, pos,FRotator::ZeroRotator,FActorSpawnParameters());
		bomb->SetInstigator(owner);
		//bomb->Sphere->SetRelativeLocation(FVector::ZeroVector);
		bomb->damageEffectSpecHandle = damageEffectSpecHandle;
	}
	FGameplayEffectSpecHandle fireEffectSpecHandle = MakeOutgoingGameplayEffectSpec(UGEBombFire::StaticClass(), GetAbilityLevel());
	bomb->fireEffectSpecHandle = fireEffectSpecHandle;
	AActor* actor = GetOwningActorFromActorInfo();
	AGDPlayerState* playerState = Cast<AGDPlayerState>(actor);
	playerState->ShowAbilityConfirmCancelText(false);
}

void UGDGABomb::OnCancel(const FGameplayAbilityTargetDataHandle& Data)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}


