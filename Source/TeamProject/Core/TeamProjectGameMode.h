// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Manager/WarningBoxManager.h"
#include "../Manager/UserWidgetManager.h"
#include "TeamProjectGameMode.generated.h"

UCLASS(minimalapi)
class ATeamProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	//UserWidgetManager& UWManager;
	WarningBoxManager* warningBoxManager;

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	void CallClassInit();// 내가 직접 만든 부모없는 클래스는 play시 constructor 가 호출이 안됨. gamemodebase의 constructor은 play시에도 생성자가 불리기 때문에 그래서 이걸로 변수 초기화를 해줄 함수를 강제로 불러줌.
public:
	ATeamProjectGameMode();
};



