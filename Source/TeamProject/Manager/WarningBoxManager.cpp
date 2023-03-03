// Fill out your copyright notice in the Description page of Project Settings.


#include "WarningBoxManager.h"
#include "../Actor/WarningBox.h"

WarningBoxManager::WarningBoxManager()
{
}

WarningBoxManager::~WarningBoxManager()
{
}

void WarningBoxManager::BeginPlay()
{

}

void WarningBoxManager::AddBoxToAry(AWarningBox* box)
{
	boxAry.Add(box);
	//TurnOnBoxes(0, 1); 테스트용
}

void WarningBoxManager::TurnOnBoxes(int32 col,int32 row)
{
	UE_LOG(LogTemp, Log, TEXT("@@ TurnOnBoxes()"));
	for (int i = 0; i < boxAry.Num(); i++)
	{
		if (boxAry[i]->GetRow() == row || boxAry[i]->GetCol() == col)
		{
			UE_LOG(LogTemp, Log, TEXT("@@ TurnOnBoxes() find!!!!!!!!!!!!"));
			boxAry[i]->TurnOnBox();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("@@ row= %d col = %d  | %d %d"),row,col, boxAry[i]->GetRow(), boxAry[i]->GetCol());
		}
	}
}

