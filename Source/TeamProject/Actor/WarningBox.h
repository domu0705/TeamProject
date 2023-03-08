// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Manager/WarningBoxManager.h"
#include "../Core/Timer.h"
#include "WarningBox.generated.h"

class WarningBosMAnager;

UCLASS()
class TEAMPROJECT_API AWarningBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarningBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents()override;
	void TurnOnBox();
	void TurnOffBox();
	void CheckTurnOffBox();
	int32 GetRow();
	int32 GetCol();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* body;
	UPROPERTY(VisibleAnywhere)
		UStaticMesh* actor;

	//void virtual NotifyActorBeginOverlap(AActor* OtherActor)override;

private:
	Timer* timer;

	//bool bHidden;
	UPROPERTY(EditAnywhere, Category = Position)//category는 UE에서 보이는 항목의 이름을 설정하는 것임.
		int32 rowNum;
	UPROPERTY(EditAnywhere, Category = Position)//category는 UE에서 보이는 항목의 이름을 설정하는 것임.
		int32 colNum;
	UPROPERTY(EditAnywhere, Category = Info)//category는 UE에서 보이는 항목의 이름을 설정하는 것임.
		bool isTurnOn;
	UPROPERTY(EditAnywhere, Category = Info)//category는 UE에서 보이는 항목의 이름을 설정하는 것임.
		int32 turnOnTime;
	UPROPERTY(EditAnywhere, Category = Info)//warning이 켜져있는 시간
		int32 turnOnDuration;
};
