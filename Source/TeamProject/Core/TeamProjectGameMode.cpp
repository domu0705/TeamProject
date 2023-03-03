// Copyright Epic Games, Inc. All Rights Reserved.

#include "TeamProjectGameMode.h"
#include "../Character/TPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATeamProjectGameMode::ATeamProjectGameMode()
{
	UE_LOG(LogTemp, Log, TEXT("@@ATeamProjectGameMode::ATeamProjectGameMode()"));
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	//DefaultPawnClass = ATPCharacter::StaticClass();

	warningBoxManager = WarningBoxManager::GetInstance();
}

void ATeamProjectGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//if (!SocketManager)
	//	return;
	//SocketManager->Tick();
}

void ATeamProjectGameMode::BeginPlay()
{
	warningBoxManager.BeginPlay();
}