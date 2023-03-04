// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatComponent.h"

// Sets default values for this component's properties
UCharacterStatComponent::UCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;//InitializeComponent() È£Ãâ À§ÇÔ
}

void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetStat();
}

// Called when the game starts
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterStatComponent::SetStat()
{
	MaxHP = 3;
	CurrentHP = MaxHP;
}

void UCharacterStatComponent::GetDamage()
{
	if (CurrentHP <= 1)
	{
		UE_LOG(LogTemp, Log, TEXT("Current HEalth = %d -> Do die"), CurrentHP);
	}
	else
	{
		--CurrentHP;
		UE_LOG(LogTemp, Log, TEXT("Current HEalth = %d"), CurrentHP);
	}

}