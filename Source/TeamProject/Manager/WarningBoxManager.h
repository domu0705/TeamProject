// -----------------------------------------------------------------------------
// warning box�� �����Ǵ� monster�� �����ϴ� Ŭ����
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
	int32 	turnOnTime ;//warning box �� ���� �ð�
	int32 duration;//warning box �� �����ִ� �ð�
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

	void Init();//gamemodebase �����ڿ��� ȣ��
	void BeginPlay();
	void Tick();
	void AddBoxToAry(AWarningBox* box);
	void AddMonsterToAry(AMonster* monster);
	void SetCurInfo(int32 inCol, int32 inRow, int32 inDir);
	void TurnOnBoxes(int32 col, int32 row, int32 dir);
	void TurnOffBoxes();
	void CheckTurnOffBox();
};
