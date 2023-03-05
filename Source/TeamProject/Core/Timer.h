// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <ctime> 
/**
 * 
 */
class TEAMPROJECT_API Timer
{
private:
	void tick();
	UPROPERTY(EditAnywhere)// VisibleAnywhere
		int32 curTime;

public:
	static Timer* GetInstance() {
		static Timer s;
		return &s;
	}

	Timer();
	~Timer();
	void SetTime(int32 time);
	int32 GetTIme();
	int32 GetCurTime();
};
