// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UI/HeadUW.h"
#include "../UI/LogInUW.h"
#include "../UI/InGameUW.h"
#include "Blueprint/UserWidget.h"


class TEAMPROJECT_API UserWidgetManager
{
private:
	TSubclassOf<UUserWidget> LobbyUWClass;
	TSubclassOf<UUserWidget> InGameUWClass;
	TSubclassOf<UUserWidget> HeadUWClass;

	UHeadUW* HeadUW;
	ULogInUW* LoginUW;
	UInGameUW* InGameUW;

public:
	static UserWidgetManager* GetInstance() {
		static UserWidgetManager s;
		return &s;
	}

	UserWidgetManager();
	~UserWidgetManager();

	void CreateHeadUW(UWorld* world);
	void CreateLogInUW(UWorld* world);
	void CreateInGameUW(UWorld* world);
	void UpdateHP(int32 inCurrentHP);

};
