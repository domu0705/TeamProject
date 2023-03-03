// Fill out your copyright notice in the Description page of Project Settings.


#include "WarningBox.h"

// Sets default values
AWarningBox::AWarningBox()//여기서 초기화 안됨. 이 이후에 블프 값으로 다시 초기화 됨
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));

	RootComponent = body;//없어도 됨
	UE_LOG(LogTemp, Log, TEXT("@@ AWarningBox() %s"), *this->GetName())
	isTurnOn = false;

	boxManager = WarningBoxManager::GetInstance();
	timer = Timer::GetInstance();
}

// Called when the game starts or when spawned
void AWarningBox::BeginPlay()
{
	UE_LOG(LogTemp, Log, TEXT("@@ AWarningBox::BeginPlay()"));
	TurnOffBox();
	boxManager.AddBoxToAry(this);
	Super::BeginPlay();
}

// Called every frame
void AWarningBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckTurnOffBox();
}

void AWarningBox::TurnOnBox()
{
	//turnOnTime = timer.GetTIme();
	turnOnTime = timer.GetCurTime();
	UE_LOG(LogTemp, Log, TEXT("@@ AWarningBox::TurnOnBox() %s %d %d"), *this->GetName(),turnOnTime, timer.GetCurTime());
	SetActorHiddenInGame(false);
	isTurnOn = true;
}

//warning box가 끌수 있는 환경인지 검사
void AWarningBox::CheckTurnOffBox()
{
	if (isTurnOn == false)
		return;
	UE_LOG(LogTemp, Log, TEXT("@@ AWarningBox::TurnOffBox() %s %d"), *this->GetName(), turnOnTime);
	if (timer.GetCurTime() > turnOnTime + 10)
	{
		TurnOffBox();
	}
}

//warning box 를 끔
void AWarningBox::TurnOffBox()
{
	SetActorHiddenInGame(true);
	isTurnOn = false;
}

int32 AWarningBox::GetRow()
{
	return rowNum;
}

int32 AWarningBox::GetCol()
{
	return colNum;
}

/*
void AWarningBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (bHidden)
		TurnOffBox();
	else
		TurnOnBox();
}
*/