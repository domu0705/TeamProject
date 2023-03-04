// Fill out your copyright notice in the Description page of Project Settings.


#include "LogInUW.h"

//버튼이벤트와 함수 연결
void ULogInUW::NativeConstruct()
{
	Super::NativeConstruct();

	PacketManager = PacketManager::GetInstance();

	if (!LogInBtn)
		return;
	LogInBtn->OnClicked.AddDynamic(this, &ULogInUW::LogInBtnClicked);
	//LogInBtn->SetVisibility(ESlateVisibility::Collapsed);
}

//로그인 요청
void ULogInUW::LogInBtnClicked()
{
	FString idStr = (IDEditText->GetText()).ToString();
	int32 tempCnt = FCString::Atoi(*idStr);

	PacketManager.SendLogin(idStr);
}
