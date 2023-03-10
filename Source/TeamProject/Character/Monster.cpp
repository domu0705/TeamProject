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
	isMoving = false;
	//overlap확인을 위한 capsule component 생성
	overlapCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MONSTERCAPSUPECOMPONENT"));
	overlapCapsule->InitCapsuleSize(75.0f, 96.f);
	overlapCapsule->SetCollisionProfileName(FName("MonsterOverlap"));

	speed = 1.0f;
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
		//UE_LOG(LogTemp, Log, TEXT("@@@ AMonster::SetCollisionProfileName()"));
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
	if (!isMoving)
		return;
	MoveFoward();
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
	isMoving = true;

	AController* controller = GetController();
	if (!controller)
		return;

	FRotator Rotation = controller->GetControlRotation();
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	//AddMovementInput(Direction, true);

	/*
	FVector curPos = GetActorLocation();
	if (isHorizontal)
	{
		float dir = (Direction.Y > 0) ? 1 : -1;
		SetActorLocation(FVector(curPos.X, curPos.Y + dir*speed, curPos.Z));
	}
	else
	{
		float dir = (Direction.X > 0) ? 1 : -1;
		SetActorLocation(FVector(curPos.X + dir * speed, curPos.Y , curPos.Z));
	}
	*/
	//SetActorLocation(curPos + Direction);
	AddMovementInput(Direction, true);
}



/*
void ATeamProjectCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}
*/