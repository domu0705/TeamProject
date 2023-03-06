// Fill out your copyright notice in the Description page of Project Settings.


#include "Timer.h"


Timer::Timer()
{
	curTime = 0;
}

Timer::~Timer()
{
}

void Timer::tick()
{

}

void Timer::SetTime(int32 time)
{
	curTime = time;
}

int32 Timer::GetTIme()
{
	return curTime;
}

int32 Timer::GetCurTime()
{
	time_t timer = time(NULL);
	struct tm* t = localtime(&timer);

	int32 sec = t->tm_sec;
	//UE_LOG(LogTemp, Log, TEXT("@@ Timer::GetCurTime() sec %d "),sec)
	return sec;
}