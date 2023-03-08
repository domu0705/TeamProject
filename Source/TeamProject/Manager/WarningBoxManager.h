// -----------------------------------------------------------------------------
// warning box�� �����Ǵ� monster�� �����ϴ� Ŭ����
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
	TArray<TArray<int32>> warningAry; // ���� ������ ���� ���� ���� ����{ {0, 1, 0}, {1,0,1}}
	Timer* timer;
	int32 	turnOnTime ;//warning box �� ���� �ð�
	int32 duration;//warning box �� �����ִ� �ð�

	//델타타임으로 누적시간 확인
	bool isTurnOn;

public:
	/*static WarningBoxManager* GetInstance() {
		static WarningBoxManager s;
		return &s;
	}*/
	static WarningBoxManager& GetInstance() {
		static WarningBoxManager i;
		return i;
	}

	WarningBoxManager();
	~WarningBoxManager();

	void Init();//gamemodebase �����ڿ��� ȣ��
	void BeginPlay();
	void Tick(float DeltaSeconds);
	void AddBoxToAry(AWarningBox* box);
	void AddMonsterSpawnerToAry(AMonsterSpawner* monster);
	void TurnOnBoxes(int32 col, int32 row, int32 dir);
	void CheckTurnOffBox();
	void TurnOffBoxes();
	void TurnOnSpawner();
};
