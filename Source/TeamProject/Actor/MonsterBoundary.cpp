// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MonsterBoundary.h"

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
	boxManager->TurnOnBoxes(0, 3, 0); //테스트용. 지금은 이거 여러번 불림
	boxManager->TurnOnBoxes(2, 0, 1);
	boxManager->TurnOnBoxes(0, 5, 0);
}

