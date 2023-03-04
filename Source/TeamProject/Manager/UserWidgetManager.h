// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UI/LogInUW.h"
#include "Blueprint/UserWidget.h"


class TEAMPROJECT_API UserWidgetManager
{
private:
	TSubclassOf<UUserWidget> LobbyUWClass;


	ULogInUW* LoginUW;

public:
	static UserWidgetManager& GetInstance() {
		static UserWidgetManager i;
		return i;
	}

	UserWidgetManager();
	~UserWidgetManager();

	void CreateLogInUW(UWorld* world);

};
