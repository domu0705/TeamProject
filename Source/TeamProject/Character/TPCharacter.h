// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TeamProjectCharacter.h"
#include "../Core/Timer.h"
#include "../Manager/UserWidgetManager.h"
#include "../Character/Monster.h"
#include "Components/WidgetComponent.h"
#include "TPCharacter.generated.h"

UCLASS()
class TEAMPROJECT_API ATPCharacter : public ATeamProjectCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPCharacter();

private:
	Timer* timer;

	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPirvateAccess = true))
		int32 MaxHP;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPirvateAccess = true))
		int32 CurrentHP;
	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPirvateAccess = true))
		bool isSuper;//무적인지 아닌지
	//무적인지 아닌지
	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPirvateAccess = true))
		int32 superStartTime;
	//무적 지속 기간
	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPirvateAccess = true))
		int32 superDuration;

	//서버에서 지정하는 캐릭터 구분 인덱스
	unsigned short index;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		class UCharacterStatComponent* CharacterStat;

	float Time1 = 0;
	float Time2 = 0;

protected:
	//로컬에서 나와 타 플레이어를 구분하기 위함
	UPROPERTY(EditAnywhere)
		FString nickName;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Colliders")
		class UCapsuleComponent* overlapCapsule;

public:	
	UPROPERTY(VIsibleAnywhere, Category = UI)
		class UWidgetComponent* headUW;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetStat();
	void ChangeOpacity();
	void GetDamage();
	void UpdateHP();
	void SetIndex(unsigned short inIndex);
	unsigned short GetIndex();
};
