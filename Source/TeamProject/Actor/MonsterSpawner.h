// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawner.generated.h"

UCLASS()
class TEAMPROJECT_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMonsterSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* body;
	UPROPERTY(VisibleAnywhere)
		TSubclassOf<class AMonster> monsterClass;
	UPROPERTY(EditAnywhere, Category = Position)
		int32 spawnerNum;// 1~7
	UPROPERTY(EditAnywhere, Category = Position)
		int32 spawnerDir;//0 or 1 (상/하  좌/우 스폰 위치 구분)
	void SpawnMonster();
};
