// Fill out your copyright notice in the Description page of Project Settings.

#include "TPCharacter.h"
#include "CharacterStatComponent.h"

// Sets default values
ATPCharacter::ATPCharacter()
{
	UE_LOG(LogTemp, Log, TEXT("@@ATPCharacter::ATPCharacter()"));
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//CharacterStat = CreateDefaultSubobject< UCharacterStatComponent>(TEXT("CHARACTERSTAT"));
	timer = Timer::GetInstance();
	SetStat();
}

// Called when the game starts or when spawned
void ATPCharacter::BeginPlay()
{
	Super::BeginPlay();
	SocketManager::GetInstance().SetCharacter(this);
	if (nickName == TEXT("myUser"))
	{

	}
	else 
	{

	}
}

// Called every frame
//void ATPCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
void ATPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATPCharacter::SetStat()
{
	MaxHP = 3;
	CurrentHP = MaxHP;
	isSuper = false;
	superDuration = 2;
}
/*
void ATPCharacter::MovePosition()
{
	// Get a reference to the player character
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// Set the new location for the player
	FVector newLocation = FVector(100.0f, 0.0f, 0.0f);
	playerCharacter->SetActorLocation(newLocation);
}
*/

void ATPCharacter::GetDamage()
{
	UE_LOG(LogTemp, Log, TEXT("ATPCharacter::GetDamage()"));
	if (isSuper)
		return;

	if (CurrentHP <= 1)//죽음
	{
		UE_LOG(LogTemp, Log, TEXT("ATPCharacter::GetDamage() | Current HEalth = %d -> Do die"), CurrentHP);
	}
	else//생명 감소
	{
		--CurrentHP;
		UE_LOG(LogTemp, Log, TEXT("Current HEalth = %d"), CurrentHP);
		isSuper = true;
		UpdateHP();
	}
}

void ATPCharacter::UpdateHP()
{
	UserWidgetManager* UserWidgetManager = UserWidgetManager::GetInstance();
	if (!UserWidgetManager)
		return;
	UserWidgetManager->UpdateHP(CurrentHP);
}