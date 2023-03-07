// Fill out your copyright notice in the Description page of Project Settings.


#include "PacketManager.h"

PacketManager::PacketManager()
{
}

PacketManager::~PacketManager()
{
}

void PacketManager::MakeLoginPacket(const FString& inID)
{
	UE_LOG(LogTemp, Log, TEXT("@@ PacketManager::SendLogin() | id : %s"), *inID)
	//FString command = FString::Printf(TEXT("LOGIN %s\r\n"), *inID);
	Packet::LoginRequestPacket loginRequestPacket(inID);
	SocketManager::GetInstance()._sendPacket(Packet::PacketID::LOGINREQUEST, &loginRequestPacket);
}

//->GetComponentRotation().Vector();
//플레이어의 움직인 좌표를 전달하는 패킷 생성
void PacketManager::MakeUpdatePacket(FVector newPos, FVector newRot)
{
	//FString command = FString::Printf(TEXT("LOGIN %s\r\n"), *inID);
	float posVec[3] = { newPos.X,newPos.Y,newPos.Z };
	float rotVec[3] = { newRot.X ,newRot.Y,newRot.Z };

	Packet::UpdatePacket updatePacket(posVec,rotVec);
	SocketManager::GetInstance()._sendPacket(Packet::PacketID::UPDATE, &updatePacket);
}
