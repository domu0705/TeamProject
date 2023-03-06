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
	Packet::LoginRequestPacket loginRequestPacket(inID);
	SocketManager& SocketManager = SocketManager::GetInstance();
	SocketManager._sendPacket(Packet::PacketID::LOGINREQUEST, &loginRequestPacket);
}