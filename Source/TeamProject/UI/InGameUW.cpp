// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUW.h"

void UInGameUW::NativeConstruct()
{
	Super::NativeConstruct();
	//LogInBtn->SetVisibility(ESlateVisibility::Collapsed);
}


void UInGameUW::UpdateHP(int32 inHP)
{
	UE_LOG(LogTemp, Log, TEXT("UInGameUW::UpdateHP() "));
	FString newHP = FString::FromInt(inHP);
	curHPText->SetText(FText::FromString(newHP));
}