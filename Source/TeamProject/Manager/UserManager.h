// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ServerConn/SocketManager.h"

class ATPCharacter;

class TEAMPROJECT_API UserManager
{

private:
	TMap<int32, ATPCharacter*> characterAry;

public:
	static UserManager* GetInstance() {
		static UserManager s;
		return &s;
	}

	UserManager();
	~UserManager();

	void AddUserAry(int32 key, ATPCharacter* inCharacter);
};
