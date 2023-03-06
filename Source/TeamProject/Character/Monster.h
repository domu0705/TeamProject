// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../ChatacterController/MonsterController.h"
#include "TeamProjectCharacter.h"
#include "Monster.generated.h"

UCLASS()
class TEAMPROJECT_API AMonster : public ATeamProjectCharacter//ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

private:
	bool isMoving;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//void virtual NotifyActorBeginOverlap(AActor* OtherActor)override;
	void MoveFoward();
};