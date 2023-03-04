// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..//ServerConn/PacketManager.h"
#include "../ServerConn/SocketManager.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "LogInUW.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ULogInUW : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
		void LogInBtnClicked();

	UFUNCTION()
		void PortConnBtnClicked();

	//PacketManager PacketManager;

public:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UButton* LogInBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UButton* PortBtn = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* IDEditText;

};
