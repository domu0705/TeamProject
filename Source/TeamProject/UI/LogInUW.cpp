// Fill out your copyright notice in the Description page of Project Settings.


#include "LogInUW.h"

//��ư�̺�Ʈ�� �Լ� ����
void ULogInUW::NativeConstruct()
{
	Super::NativeConstruct();

	PacketManager = PacketManager::GetInstance();

	if (!LogInBtn)
		return;
	LogInBtn->OnClicked.AddDynamic(this, &ULogInUW::LogInBtnClicked);
	//LogInBtn->SetVisibility(ESlateVisibility::Collapsed);
}

//�α��� ��û
void ULogInUW::LogInBtnClicked()
{
	FString idStr = (IDEditText->GetText()).ToString();
	int32 tempCnt = FCString::Atoi(*idStr);

	PacketManager.SendLogin(idStr);
}
