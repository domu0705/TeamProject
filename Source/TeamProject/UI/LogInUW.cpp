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
	//LogInBtn->SetVisibility(ESlateVisibility::Collapsed);
}

//로그인 요청
void ULogInUW::LogInBtnClicked()
{
	FString idStr = (IDEditText->GetText()).ToString();
	int32 tempCnt = FCString::Atoi(*idStr);
	PacketManager& PacketManager = PacketManager::GetInstance();
	PacketManager.MakeLoginPacket(idStr);
}

//포트 연결 요청
void ULogInUW::PortConnBtnClicked()
{
	SocketManager& socketManager = SocketManager::GetInstance();

	if (socketManager.ConnectServer())
	{
		//PortBtn->SetVisibility(ESlateVisibility::Collapsed);
		//LogInBtn->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Log, TEXT("@@@ port conn soccess"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ port conn failed"));
	}
}