// Fill out your copyright notice in the Description page of Project Settings.


#include "WarningBoxManager.h"
#include "../Actor/WarningBox.h"

WarningBoxManager::WarningBoxManager()
{
	UE_LOG(LogTemp, Log, TEXT("** WarningBoxManager::WarningBoxManager()"));
	timer = Timer::GetInstance();
}

WarningBoxManager::~WarningBoxManager()
{
}

void WarningBoxManager::Init()
{
	UE_LOG(LogTemp, Log, TEXT("**WarningBoxManager::BeginPlay()"));
	boxAry .Empty();
	isTurnOn = false;
	duration = 5;
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
	TurnOnBoxes(0, 1,0); //테스트용
}

void WarningBoxManager::AddMonsterToAry(AMonster* monster)
{
	monsterAry.Add(monster);
}


void  WarningBoxManager::SetCurInfo(int32 inCol, int32 inRow, int32 inDir)
{
	curCol = inCol;
	curRow = inRow;
	curDir = inDir;
}

void WarningBoxManager::TurnOnBoxes(int32 col,int32 row,int32 dir)
{
	turnOnTime = timer->GetCurTime();
	isTurnOn = true;
	SetCurInfo(col, row, dir);

	UE_LOG(LogTemp, Log, TEXT("@@ WarningBoxManager::TurnOnBoxes()"));
	
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

void WarningBoxManager::CheckTurnOffBox()
{
	UE_LOG(LogTemp, Log, TEXT("@@ AWarningBox::TurnOnBox() %d %d %"), turnOnTime, timer->GetCurTime());
	if (isTurnOn == false)
	{
		UE_LOG(LogTemp, Log, TEXT("isturnon false"));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("isturnon true"));
	}

	if (timer->GetCurTime() > turnOnTime + duration)
	{
		UE_LOG(LogTemp, Log, TEXT("&& AWarningBox::CheckTurnOffBox() %d"),turnOnTime);
		TurnOffBoxes();
	}
}

void WarningBoxManager::TurnOffBoxes()
{
	isTurnOn = false;

	for (int i = 0; i < boxAry.Num(); i++)
	{
		if (boxAry[i]->GetRow() == curRow || boxAry[i]->GetCol() == curCol)
		{
			UE_LOG(LogTemp, Log, TEXT("@@ WarningBoxManager::TurnOffBoxes()"));
			boxAry[i]->SetActorHiddenInGame(true);
		}
	}
}