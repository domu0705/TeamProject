// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AWarningBox;

class TEAMPROJECT_API WarningBoxManager
{

private:
	TArray<AWarningBox*> boxAry;

public:
	static WarningBoxManager& GetInstance() {
		static WarningBoxManager i;
		return i;
	}


	WarningBoxManager();
	~WarningBoxManager();

	void BeginPlay();
	void AddBoxToAry(AWarningBox* box);
	void TurnOnBoxes(int32 col, int32 row);
};
