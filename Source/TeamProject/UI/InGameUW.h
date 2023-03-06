// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "InGameUW.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UInGameUW : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	void UpdateHP(int32 inHP);

	UPROPERTY(meta = (BindWidget))
		UTextBlock* curHPText = nullptr;
};
