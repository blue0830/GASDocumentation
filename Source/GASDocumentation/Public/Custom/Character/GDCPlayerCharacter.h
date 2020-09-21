// Copyright 2020 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GDCharacterBase.h"
#include "GDCPlayerCharacter.generated.h"

UCLASS()
class GASDOCUMENTATION_API AGDCPlayerCharacter : public AGDCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGDCPlayerCharacter(const class FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	class USpringArmComponent* GetCameraBoom();

	class UCameraComponent* GetFollowCamera();

protected:

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category="Custom|Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category="Custom|Camera")
	class UCameraComponent* FollowCamera;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	USkeletalMeshComponent* GunComponent;

	TSubclassOf<class UGDFloatingStatusBarWidget> UIHpBarClass;

	class UGDFloatingStatusBarWidget* UIHpBar;

	class UWidgetComponent* UIHpBarComponent;

	// Mouse
	void LookUp(float Value);

	// Gamepad
	void LookUpRate(float Value);

	// Mouse
	void Turn(float Value);

	// Gamepad
	void TurnRate(float Value);

	// Mouse + Gamepad
	void MoveForward(float Value);

	// Mouse + Gamepad
	void MoveRight(float Value);



};
