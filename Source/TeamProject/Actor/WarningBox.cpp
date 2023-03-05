// Fill out your copyright notice in the Description page of Project Settings.


#include "WarningBox.h"

// Sets default values
AWarningBox::AWarningBox()//여기서 초기화 안됨. 이 이후에 블프 값으로 다시 초기화 됨
{
	UE_LOG(LogTemp, Log, TEXT("** AWarningBox::AWarningBox()"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));

	RootComponent = body;//없어도 됨
	//UE_LOG(LogTemp, Log, TEXT("@@ AWarningBox() %s"), *this->GetName())

	boxManager = WarningBoxManager::GetInstance();
	timer = Timer::GetInstance();
	turnOnDuration = 5;
}

// Called when the game starts or when spawned
void AWarningBox::BeginPlay()
{
	Super::BeginPlay();
	boxManager->AddBoxToAry(this);

	//isTurnOn = false;
	//UE_LOG(LogTemp, Log, TEXT("@@ AWarningBox::BeginPlay()"));
}

// Called every frame
void AWarningBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckTurnOffBox();
}

void AWarningBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//UE_LOG(LogTemp, Log, TEXT("@@ AWarningBox::BeginPlay()"));
	TurnOffBox();
}
void AWarningBox::TurnOnBox()
{
	//turnOnTime = timer.GetTIme();
	turnOnTime = timer->GetCurTime();
	UE_LOG(LogTemp, Log, TEXT("@@ AWarningBox::TurnOnBox() %s %d %d"), *this->GetName(), turnOnTime, timer->GetCurTime());
	SetActorHiddenInGame(false);
	isTurnOn = true;
}

//warning box가 끌수 있는 환경인지 검사
void AWarningBox::CheckTurnOffBox()
{
	if (isTurnOn == false)
		return;
	UE_LOG(LogTemp, Log, TEXT("@@ AWarningBox::CheckTurnOffBox() %s %d"), *this->GetName(), turnOnTime);
	if (timer->GetCurTime() > turnOnTime + turnOnDuration)
	{
		TurnOffBox();
	}
}

//warning box 를 끔
void AWarningBox::TurnOffBox()
{
	UE_LOG(LogTemp, Log, TEXT("## AWarningBox::TurnOffBox()"), *this->GetName(), turnOnTime);
	SetActorHiddenInGame(true);
	isTurnOn = false;
	boxManager->TurnOnSpawner();
}

int32 AWarningBox::GetRow()
{
	return rowNum;
}

int32 AWarningBox::GetCol()
{
	return colNum;
}
