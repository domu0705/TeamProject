// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Manager/WarningBoxManager.h"
#include "TeamProjectGameMode.generated.h"

UCLASS(minimalapi)
class ATeamProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	WarningBoxManager warningBoxManager;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
public:
	ATeamProjectGameMode();
};



