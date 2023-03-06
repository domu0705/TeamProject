// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include "../Character/Monster.h"
#include "../Manager/WarningBoxManager.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));

	WarningBoxManager = WarningBoxManager::GetInstance();
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	WarningBoxManager->AddMonsterSpawnerToAry(this);
	//SpawnMonster();
}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 AMonsterSpawner::GetColNum()
{
	return colNum;
}

int32 AMonsterSpawner::GetRowNum()
{
	return rowNum;
}

int32 AMonsterSpawner::GetSpawnerDir()
{
	return dirNum;
}

void AMonsterSpawner::SpawnMonster()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FString path = TEXT("/Game/Characters/BP_Monster");
	monsterClass = ConstructorHelpersInternal::FindOrLoadClass(path, AMonster::StaticClass());
	if (!monsterClass) return;

	FVector spawnLocation = GetActorLocation();
	spawnLocation.Z += 30.f;
	FRotator spawnRotation = GetActorRotation();
	//spawnRotation.Yaw += 90.0f;
	UE_LOG(LogTemp, Log, TEXT("@@ spawnRotation = "));
	AMonster* newMonster = GetWorld()->SpawnActor<AMonster>(monsterClass, spawnLocation, spawnRotation, SpawnParams);
	if (!newMonster) return;
	newMonster->MoveFoward();
}


