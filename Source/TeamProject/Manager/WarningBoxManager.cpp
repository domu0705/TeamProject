// Fill out your copyright notice in the Description page of Project Settings.


#include "WarningBoxManager.h"
#include "../Actor/WarningBox.h"

WarningBoxManager::WarningBoxManager()
{
	timer = Timer::GetInstance();
}

WarningBoxManager::~WarningBoxManager()
{
}

void WarningBoxManager::Init()
{
	boxAry .Empty();
	spawnerAry.Empty();
	isTurnOn = false;
	duration = 2;
}

void WarningBoxManager::BeginPlay()
{
}

void WarningBoxManager::Tick()
{
	CheckTurnOffBox();
}

void WarningBoxManager::AddBoxToAry(AWarningBox* box)
{
	boxAry.Add(box);
	if (boxAry.Num()<48)
		return;

	//col,row,dir
	//TurnOnBoxes(0, 3,0); //테스트용. 지금은 이거 여러번 불림
	//TurnOnBoxes(2, 0, 1);
	//TurnOnBoxes(0, 5, 0);
}

void WarningBoxManager::AddMonsterSpawnerToAry(AMonsterSpawner* spawner)
{
	spawnerAry.Add(spawner);
}

void WarningBoxManager::TurnOnBoxes(int32 col,int32 row,int32 dir)
{
	warningAry.Add({ col,row,dir });
	turnOnTime = timer->GetCurTime();
//	isTurnOn = true;
	//SetCurInfo(col, row, dir);

	//UE_LOG(LogTemp, Log, TEXT("@@ WarningBoxManager::TurnOnBoxes()"));
	
	for (int i = 0; i < boxAry.Num(); i++)
	{
		if (boxAry[i]->GetRow() == row || boxAry[i]->GetCol() == col)
		{
			boxAry[i]->TurnOnBox();
		}
		else
		{
			//UE_LOG(LogTemp, Log, TEXT("@@ row= %d col = %d  | %d %d"),row,col, boxAry[i]->GetRow(), boxAry[i]->GetCol());
		}
	}
}

void WarningBoxManager::CheckTurnOffBox()//안씀
{;
	if (warningAry.Num() == 0)
	{
		return;
	}

	if (timer->GetCurTime() > turnOnTime + duration)
	{
		UE_LOG(LogTemp, Log, TEXT("&& AWarningBox::CheckTurnOffBox() %d"), turnOnTime);
		TurnOffBoxes();
	}
}

void WarningBoxManager::TurnOffBoxes()
{
	for (int i = 0; i < boxAry.Num(); i++)
	{
		if (warningAry.Num() == 0)//TurnOnBoxes 가 테스트에서는 과하게 많이 불려서 이거 검사함
			return;
		if (boxAry[i]->GetRow() == warningAry[0][1] || boxAry[i]->GetCol() == warningAry[0][0])
		{
			UE_LOG(LogTemp, Log, TEXT("@@ WarningBoxManager::TurnOffBoxes()"));
			boxAry[i]->SetActorHiddenInGame(true);
		}
	}
	TurnOnSpawner();
}

void WarningBoxManager::TurnOnSpawner()
{
	UE_LOG(LogTemp, Log, TEXT("@@ WarningBoxManager::TurnOnSpawner()"));
	if (warningAry.Num() == 0)//TurnOnBoxes 가 테스트에서는 과하게 많이 불려서 이거 검사함
		return;

	for (int i = 0; i < spawnerAry.Num(); i++)
	{
		
		if (spawnerAry[i]->GetColNum()  == warningAry[0][0] && spawnerAry[i]->GetRowNum() == warningAry[0][1] && spawnerAry[i]->GetSpawnerDir() == warningAry[0][2])
		{
			UE_LOG(LogTemp, Log, TEXT("@@ CALL SpawnMonster()"));
			spawnerAry[i]->SpawnMonster();
		}
	}
	warningAry.RemoveAt(0);
}