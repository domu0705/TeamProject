// -----------------------------------------------------------------------------
// warning box와 스폰되는 monster를 관리하는 클래스
// -----------------------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "../Core/Timer.h"
#include "../Character/Monster.h"
#include "../Actor/MonsterSpawner.h"

class AWarningBox;

class TEAMPROJECT_API WarningBoxManager
{

private:
	TArray<AWarningBox*> boxAry;
	//TArray<AMonster*> monsterAry;
	TArray<AMonsterSpawner*> spawnerAry;
	TArray<TArray<int32>> warningAry; // 몬스터 스폰을 위해 워닝 정보 저장{ {0, 1, 0}, {1,0,1}}
	Timer* timer;
	int32 	turnOnTime ;//warning box 가 켜진 시간
	int32 duration;//warning box 가 켜저있는 시간
	bool isTurnOn;

public:
	static WarningBoxManager* GetInstance() {
		static WarningBoxManager s;
		return &s;
	}

	WarningBoxManager();
	~WarningBoxManager();

	void Init();//gamemodebase 생성자에서 호출
	void BeginPlay();
	void Tick();
	void AddBoxToAry(AWarningBox* box);
	void AddMonsterSpawnerToAry(AMonsterSpawner* monster);
	void TurnOnBoxes(int32 col, int32 row, int32 dir);
	void TurnOffBoxes();
	void TurnOnSpawner();
};
