// Fill out your copyright notice in the Description page of Project Settings.


#include "LogInUW.h"

//버튼이벤트와 함수 연결
void ULogInUW::NativeConstruct()
{
	Super::NativeConstruct();

	if (!LogInBtn)
		return;
	LogInBtn->OnClicked.AddDynamic(this, &ULogInUW::LogInBtnClicked);
	if (!PortBtn)
		return;
	PortBtn->OnClicked.AddDynamic(this, &ULogInUW::PortConnBtnClicked);

	//TurnOffUW(); //테스트 시 로그인 UI건너뛰기
	//LogInBtn->SetVisibility(ESlateVisibility::Collapsed);
}

//로그인 요청
void ULogInUW::LogInBtnClicked()
{
	const FString idStr = (IDEditText->GetText()).ToString();
	int32 tempCnt = FCString::Atoi(*idStr);
	PacketManager& PacketManager = PacketManager::GetInstance();
	PacketManager.MakeLoginPacket(idStr);
	SocketManager::GetInstance().SetMyID(idStr);
	TurnOffUW();
}

//포트 연결 요청
void ULogInUW::PortConnBtnClicked()
{
	if (SocketManager::GetInstance().ConnectServer())
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ port conn soccess"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ port conn failed"));
	}
}

void ULogInUW::TurnOffUW()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
	//LoginUI->SetVisibility(ESlateVisibility::Collapsed);
}