// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetManager.h"

UserWidgetManager::UserWidgetManager()
{
}

UserWidgetManager::~UserWidgetManager()
{
}

void UserWidgetManager::CreateLogInUW(UWorld* world)
{
	if (!world)
		return;

	FString path = "/Game/BP_UI/BP_LogIn";
	LobbyUWClass = ConstructorHelpersInternal::FindOrLoadClass(path, ULogInUW::StaticClass());
	if (!LobbyUWClass)
		return;

	LoginUW = Cast<ULogInUW>(CreateWidget<UUserWidget>(world, LobbyUWClass));
	if (LoginUW)
	{
		LoginUW->AddToViewport();
		//OnOffLobbyView(false);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ LobbyUIObject  fail "));
	}
}

void UserWidgetManager::CreateInGameUW(UWorld* world)
{
	if (!world)
		return;

	FString path = "/Game/BP_UI/BP_InGame";
	InGameUWClass = ConstructorHelpersInternal::FindOrLoadClass(path, UInGameUW::StaticClass());
	if (!InGameUWClass)
		return;

	InGameUW = Cast<UInGameUW>(CreateWidget<UUserWidget>(world, InGameUWClass));
	if (InGameUW)
	{
		InGameUW->AddToViewport();
		//OnOffLobbyView(false);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ LobbyUIObject  fail "));
	}
}

void UserWidgetManager::UpdateHP(int32 inCurrentHP)
{
	UE_LOG(LogTemp, Log, TEXT("UserWidgetManager::UpdateHP() "));
	InGameUW->UpdateHP(inCurrentHP);
}