// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBoundary.h"

// Sets default values
AMonsterBoundary::AMonsterBoundary()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMonsterBoundary::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterBoundary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterBoundary::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMovved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("AMonsterBoundary::NotifyHit"));

}

