// Fill out your copyright notice in the Description page of Project Settings.

#include "TPCharacter.h"
#include "CharacterStatComponent.h"

// Sets default values
ATPCharacter::ATPCharacter()
{
	UE_LOG(LogTemp, Log, TEXT("@@ATPCharacter::ATPCharacter()"));
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CharacterStat = CreateDefaultSubobject< UCharacterStatComponent>(TEXT("CHARACTERSTAT"));
}

// Called when the game starts or when spawned
void ATPCharacter::BeginPlay()
{
	Super::BeginPlay();
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

