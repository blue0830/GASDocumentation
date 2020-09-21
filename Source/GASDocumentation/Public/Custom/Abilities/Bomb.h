// Copyright 2020 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffect.h"
#include "Bomb.generated.h"

UCLASS()
class GASDOCUMENTATION_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnRep_ReplicatedMovement() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent,class AActor* OtherActor,class UPrimitiveComponent* OtherComponent,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

public:
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UStaticMeshComponent* Sphere;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	class USphereComponent* SphereCollision;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	FGameplayEffectSpecHandle damageEffectSpecHandle;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	FGameplayEffectSpecHandle fireEffectSpecHandle;

};
