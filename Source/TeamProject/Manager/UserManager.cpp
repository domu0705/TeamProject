// Fill out your copyright notice in the Description page of Project Settings.


#include "UserManager.h"

UserManager::UserManager()
{
}

UserManager::~UserManager()
{
}

void UserManager::AddUserAry(int32 key, ATPCharacter* inCharacter)
{
	characterAry.Add(key, inCharacter);
}
