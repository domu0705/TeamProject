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
	//서버로부터 받는 현재 누적 시간(초)
	UPROPERTY(EditAnywhere)// VisibleAnywhere
		int32 curTime;

public:
	/*static Timer* GetInstance() {
		static Timer s;
		return &s;
	}*/
	static Timer& GetInstance()
	{
		static Timer i;
		return i;
	}

	Timer();
	~Timer();
	void SetTime(int32 time);
	int32 GetTIme();
	//nt32 GetCurTime();
};
