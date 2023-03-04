// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
//#include "Components/PrimitiveComponent.h"

// Sets default values
AMonster::AMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AMonsterController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MOSTER(TEXT("/Game/TPAssets/Test/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_MOSTER.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MOSTER.Object);
	}

}

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Get a reference to the root component of the actor
	UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(RootComponent);
	if (RootComp)
	{
		// Set the collision profile to "MyCollisionProfile"
		RootComp->SetCollisionProfileName(FName("Monster"));
		UE_LOG(LogTemp, Log, TEXT("@@@ AMonster::SetCollisionProfileName()"));
	}
}



// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster::NotifyActorBeginOverlap(AActor* OtherActor)
{
	FString  name = OtherActor->GetName();
	UE_LOG(LogTemp, Log, TEXT("!! AMonster::NotifyActorBeginOverlap name = %s"), *name);
}

void AMonster::MoveFoward()
{
	AController* controller = GetController();
	if (!controller)
		return;
	const FRotator Rotation = controller->GetControlRotation();
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

	// Move the character forward in the specified direction
	AddMovementInput(Direction, 1.0f);
}

