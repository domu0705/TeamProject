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