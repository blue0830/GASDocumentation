// Copyright 2020 Dan Kestranek.


#include "Custom/Character/GDCPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AGDCPlayerCharacter::AGDCPlayerCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0, 0, 68.49));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	FollowCamera->SetupAttachment((CameraBoom));
	FollowCamera->FieldOfView = 80.0f;

	GunComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Gun"));

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	USkeletalMeshComponent* mesh = GetMesh();
	mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mesh->SetCollisionProfileName(FName("NoCollision"));

	UIHpBarComponent = CreateDefaultSubobject<UWidgetComponent>(FName("UIHpBarComponent"));
	UIHpBarComponent->SetRelativeLocation(FVector(0, 0, 120));
	UIHpBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	UIHpBarComponent->SetDrawSize(FVector2D(500, 500));

	UIHpBarClass = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/GASDocumentation/UI/UI_FloatingStatusBar_Hero.UI_FloatingStatusBar_Hero_C"));


}

// Called when the game starts or when spawned
void AGDCPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGDCPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGDCPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGDCPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGDCPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AGDCPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGDCPlayerCharacter::LookUpRate);
	PlayerInputComponent->BindAxis("Turn", this, &AGDCPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGDCPlayerCharacter::TurnRate);

}

void AGDCPlayerCharacter::PossessedBy(AController* NewController) 
{

}

void AGDCPlayerCharacter::MoveForward(float Value) {

}

void AGDCPlayerCharacter::MoveRight(float Value) {

}

void AGDCPlayerCharacter::LookUp(float Value)
{

}

void AGDCPlayerCharacter::LookUpRate(float Value)
{

}

void AGDCPlayerCharacter::Turn(float Value) {

}

void AGDCPlayerCharacter::TurnRate(float Value) {

}