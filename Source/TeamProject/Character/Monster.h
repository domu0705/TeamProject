// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../ChatacterController/MonsterController.h"
#include "TeamProjectCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Monster.generated.h"

UCLASS()
class TEAMPROJECT_API AMonster : public ACharacter//ATeamProjectCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

private:
	bool isMoving;
	//스포너에서 초기화함
	bool isHorizontal;
	float speed;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Colliders")
		class UCapsuleComponent* overlapCapsule;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void SetIsHorizontal(bool inIsHorizontal) { isHorizontal = inIsHorizontal; }
	bool GetIsHorizontal() { return isHorizontal; }
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveFoward();
};
