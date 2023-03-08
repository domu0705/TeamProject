// Copyright Epic Games, Inc. All Rights Reserved.

#include "TeamProjectGameMode.h"
#include "../Character/TPCharacter.h"
#include "../ChatacterController/TPPlayerController.h"
#include "../Character/TeamProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATeamProjectGameMode::ATeamProjectGameMode()
{

	UE_LOG(LogTemp, Log, TEXT("**ATeamProjectGameMode::ATeamProjectGameMode()"));
	PrimaryActorTick.bCanEverTick = true;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//PlayerControllerClass = ATPPlayerController::StaticClass();

	CallClassInit();

}

void ATeamProjectGameMode::CallClassInit()
{
	WarningBoxManager::GetInstance().Init();
	SocketManager::GetInstance().Init();
}

void ATeamProjectGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//if (!SocketManager)
	//	return;-gam
	SocketManager::GetInstance().Tick();
	//UE_LOG(LogTemp, Log, TEXT("@@ATeamProjectGameMode::Tick()"));
	WarningBoxManager::GetInstance().Tick(DeltaSeconds);
}

void ATeamProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

	WarningBoxManager::GetInstance().BeginPlay();

	UserWidgetManager* UserWidgetManager = UserWidgetManager::GetInstance();
	if (!UserWidgetManager)
		return;
	//UserWidgetManager = UserWidgetManager::GetInstance();

	//UI »ý¼º
	UserWidgetManager->CreateLogInUW(GetWorld());
	UserWidgetManager->CreateInGameUW(GetWorld());
}