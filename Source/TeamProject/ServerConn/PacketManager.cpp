// Fill out your copyright notice in the Description page of Project Settings.


#include "PacketManager.h"

PacketManager::PacketManager()
{
}

PacketManager::~PacketManager()
{
}

//로그인 요청
void PacketManager::MakeLoginPacket(const FString& inID)
{
	UE_LOG(LogTemp,Log,TEXT("@@ PacketManager::SendLogin() | id : %s"),*inID)
	//FString command = FString::Printf(TEXT("LOGIN %s\r\n"), *inID);
	LoginPacket loginPacket(inID);
	SocketManager& SocketManager = SocketManager::GetInstance();
	SocketManager.sendPacket(loginPacket);
}