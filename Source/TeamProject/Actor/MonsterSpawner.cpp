// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include "../Character/Monster.h"


// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));

	monsterClass = AMonster::StaticClass();
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnMonster();
}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterSpawner::SpawnMonster()
{
	FVector bodyPos = body->GetComponentLocation();
	FRotator bodyRot = body->GetComponentRotation();
	//FVector SpawnLocation(0.0f, 0.0f, 20.0f);
	//FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto newMonster = GetWorld()->SpawnActor<AMonster>(monsterClass, bodyPos, bodyRot, SpawnParams);
	//auto newMonster = GetWorld()->SpawnActor<AMonster>(monsterClass, FVector::ZeroVector, FRotator::ZeroRotator);
	//UE_LOG(LogTemp, Log, TEXT("@@@SpawnMonster()"));
	UE_LOG(LogTemp, Warning, TEXT("New monster spawned at location (%f, %f, %f)"), bodyPos.X, bodyPos.Y, bodyPos.Z);

}


