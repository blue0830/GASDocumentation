// Copyright 2020 Dan Kestranek.


#include "Custom/Abilities/Bomb.h"
#include "Components/SphereComponent.h"
#include "Characters/GDCharacterBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(FName("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetSphereRadius(51);

	//RootComponent = SphereCollision;

	//Sphere = CreateDefaultSubobject<UStaticMeshComponent>(FName("Sphere"));
	//Sphere->SetupAttachment(SphereCollision);
	//Sphere->SetRelativeLocation(FVector::ZeroVector);
	//Sphere->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	//if (SphereMeshAsset.Succeeded()) {
	//	Sphere->SetStaticMesh(SphereMeshAsset.Object);
	//}
	////Sphere->SetUsingAbsoluteLocation(true);

	//static ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterialAsset(TEXT("Material'/Game/GASDocumentation/Characters/Hero/Abilities/Meteor/Effects/Masters/M_Trans_MeshEmit_Master.M_Trans_MeshEmit_Master'"));
	//if (SphereMaterialAsset.Succeeded()) {
	//	Sphere->SetMaterial(0,SphereMaterialAsset.Object);
	//}

	
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
//	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC, ECollisionResponse::ECR_Ignore);
//	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Ignore);
}

void ABomb::OnRep_ReplicatedMovement()
{
	Super::OnRep_ReplicatedMovement();
	
}


// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Sphere->SetRelativeLocation(FVector::ZeroVector);
}

void ABomb::OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent,class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (OtherActor == this) return;
	if (!HasAuthority()) {
		//Remote
		Destroy();
		return;
	}
	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors, AGDCharacterBase::StaticClass());
	bool CanTrigger = false;
	for (int i = 0; i < overlappingActors.Num(); i++) {
		AActor* actor = overlappingActors[i];
		AGDCharacterBase* overlapActor = Cast<AGDCharacterBase>(actor);
		if (!overlapActor->IsAlive()) continue;
		UAbilitySystemComponent* abilitySystemComponent = overlapActor->GetAbilitySystemComponent();
		if(!abilitySystemComponent){
			continue;
		}
		CanTrigger = true;
		//FGameplayEffectSpecHandle gameEffectSpecHandle = MakeOut
		//const FGameplayEffectSpecHandle tmpDamageEffectSpecHandle = damageEffectSpecHandle;
		//const FGameplayEffectSpec tmpFireEffectSpecHandle = fireEffectSpecHandle;
		abilitySystemComponent->BP_ApplyGameplayEffectSpecToSelf(damageEffectSpecHandle);
		abilitySystemComponent->BP_ApplyGameplayEffectSpecToSelf(fireEffectSpecHandle);
	}
	if (!CanTrigger) return;
	Destroy();

}

