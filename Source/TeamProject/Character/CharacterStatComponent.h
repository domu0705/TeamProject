// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAMPROJECT_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;//363p
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetStat();
	void GetDamage();
private:
	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPirvateAccess = true))
		int32 MaxHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPirvateAccess = true))
		int32 CurrentHP;
};
