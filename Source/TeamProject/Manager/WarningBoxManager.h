// -----------------------------------------------------------------------------
// warning box와 스폰되는 monster를 관리하는 클래스
// -----------------------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "../Core/Timer.h"
#include "../Character/Monster.h"

class AWarningBox;

class TEAMPROJECT_API WarningBoxManager
{

private:
	TArray<AWarningBox*> boxAry;
	TArray<AMonster*> monsterAry;
	Timer* timer;
	int32 	turnOnTime ;//warning box 가 켜진 시간
	int32 duration;//warning box 가 켜저있는 시간
	bool isTurnOn;

	int32 curCol;
	int32 curRow;
	int32 curDir;

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
	void AddMonsterToAry(AMonster* monster);
	void SetCurInfo(int32 inCol, int32 inRow, int32 inDir);
	void TurnOnBoxes(int32 col, int32 row, int32 dir);
	void TurnOffBoxes();
	void CheckTurnOffBox();
};
