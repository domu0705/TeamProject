// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ServerConn/Packet.h"
#include "SocketManager.h"

class TEAMPROJECT_API PacketManager
{
private:
	//SocketManager& SocketManager;

public:
	static PacketManager& GetInstance() {
		static PacketManager i;
		return i;
	}

	PacketManager();
	~PacketManager();

	void MakeLoginPacket(const FString& inID);

};
