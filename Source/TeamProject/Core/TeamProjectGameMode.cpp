// Copyright Epic Games, Inc. All Rights Reserved.

#include "TeamProjectGameMode.h"
#include "../Character/TPCharacter.h"
//#include "../Character/TeamProjectCharacter.h"
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
}
