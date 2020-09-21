// Copyright 2020 Dan Kestranek.


#include "Custom/Abilities/BombTargetActor.h"
//#include "GameFramework/GameplayAbility.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/GDPlayerController.h"
#include "Characters/Heroes/GDHeroCharacter.h"
#include "UI/GDHUDWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Abilities/GameplayAbility.h"


ABombTargetActor::ABombTargetActor() {

	PrimaryActorTick.bCanEverTick = true;
	decal = CreateDefaultSubobject<UDecalComponent>(FName("Decal"));
	decal->SetupAttachment(RootComponent);
	decal->SetRelativeRotation(FRotator(90, -180, -180));
	//decal->SetUsingAbsoluteRotation(true);
	ConstructorHelpers::FObjectFinder<UMaterial> materialAsset(TEXT("Material'/Game/GASDocumentation/Characters/Shared/Targeting/Materials/M_TargetingCircle_Decal.M_TargetingCircle_Decal'"));
	if (materialAsset.Succeeded()) {
		decal->SetDecalMaterial(materialAsset.Object);
	}
	IsStartTargeting = false;
}

void ABombTargetActor::StartTargeting(UGameplayAbility* InAbility)
{
	//Super::StartTargeting(InAbility);
	OwningAbility = InAbility;
	IsStartTargeting = true;
	AActor* owner = InAbility->GetOwningActorFromActorInfo();
	const FGameplayAbilityActorInfo* actorInfo = InAbility->GetCurrentActorInfo();
	character = Cast<AGDHeroCharacter>(actorInfo->AvatarActor);
	//character->GunComponent->sight
	playerController = Cast<AGDPlayerController>(character->Controller);
	UIWidget = playerController->GetHUD();

	UCanvasPanel* canvasPanel = Cast<UCanvasPanel>(UIWidget->GetWidgetFromName("CanvasPanel_Reticle"));
	UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(canvasPanel->Slot);
	aimSightsPosition = canvasPanelSlot->GetPosition();
	int sizeX = GetWorld()->GetGameViewport()->Viewport->GetSizeXY().X;
	int sizeY = GetWorld()->GetGameViewport()->Viewport->GetSizeXY().Y;
	screenSize = FVector2D(sizeX, sizeY);
	
	
}

void ABombTargetActor::ConfirmTargetingAndContinue()
{
	

	//// ¼Ì³Ð×ÔFGameplayAbilityTargetData
	FGameplayAbilityTargetData_LocationInfo* ReturnData = new FGameplayAbilityTargetData_LocationInfo();

	//// Source Transform
	//ReturnData->SourceLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	//ReturnData->SourceLocation.LiteralTransform = FTransform(SourceLocation);
	//// Destination Transform
	ReturnData->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	ReturnData->TargetLocation.LiteralTransform = RootComponent->GetComponentTransform();//decal->GetComponentTransform();/*FTransform((TargetLocation - SourceLocation).ToOrientationQuat(), TargetLocation);*/

	FGameplayAbilityTargetDataHandle Handle(ReturnData);
	
	// Fire delegate with data handle !!!
	TargetDataReadyDelegate.Broadcast(Handle);
}

void ABombTargetActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!IsStartTargeting) return;
	
	
	FHitResult hitResult;
	

	playerController->GetHitResultAtScreenPosition(aimSightsPosition + screenSize/2, ECC_WorldStatic, false, hitResult);

	if (hitResult.bBlockingHit) {
		FVector location = hitResult.Location;
		location.Z = 220;
		SetActorLocation(location );
	}

}
