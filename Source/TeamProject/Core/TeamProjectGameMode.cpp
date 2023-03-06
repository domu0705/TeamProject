// Copyright Epic Games, Inc. All Rights Reserved.

#include "TeamProjectGameMode.h"
#include "../Character/TPCharacter.h"
#include "../ChatacterController/TPPlayerController.h"
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

	warningBoxManager = WarningBoxManager::GetInstance();
	CallClassInit();

}

void ATeamProjectGameMode::CallClassInit()
{
	warningBoxManager->Init();
}

void ATeamProjectGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//if (!SocketManager)
	//	return;
	//SocketManager->Tick();
	//UE_LOG(LogTemp, Log, TEXT("@@ATeamProjectGameMode::Tick()"));
	warningBoxManager->Tick();
}

void ATeamProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

	WarningBoxManager* WarningBoxManager = WarningBoxManager::GetInstance();
	if (!WarningBoxManager)
		return;
	WarningBoxManager->BeginPlay();

	UserWidgetManager* UserWidgetManager = UserWidgetManager::GetInstance();
	if (!UserWidgetManager)
		return;
	//UserWidgetManager = UserWidgetManager::GetInstance();

	//UI »ý¼º
	UserWidgetManager->CreateLogInUW(GetWorld());
	UserWidgetManager->CreateInGameUW(GetWorld());
}