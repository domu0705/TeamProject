// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Packet.h"
#include "UObject/NoExportTypes.h"
#include "Engine.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include <locale.h>

class TEAMPROJECT_API SocketManager
{
	enum
	{
		BUFFER_SIZE = 2048,
		PORT = 8080
	};

private:
	FSocket* socket;
	uint8 buffer[BUFFER_SIZE] = { 0 };
	int recvBytes = 0;
public:
	static SocketManager& GetInstance() {
		static SocketManager i;
		return i;
	}

	bool isConnected;

	SocketManager();
	~SocketManager();

	void Tick();
	bool ConnectServer();
	//void Send(FString& string);
	//void SendLogin(LoginPacket& loginPacket);
	void CheckRecvMsg(FString& recvStr, FString& str1);

	template< class PacketType >
	void sendPacket(const PacketType& packet)
	{
		//int32 len = 0;// 계산 필요
		int32 bytesSents = 0;
		const FString packetStr(reinterpret_cast<const TCHAR*>(&packet));
		FTCHARToUTF8 Converter(*packetStr);
		const char* multiByteString = (const char*)Converter.Get();
		int32 len = FCStringAnsi::Strlen(multiByteString);

		socket->Send((uint8*)(multiByteString), len, bytesSents);
		UE_LOG(LogTemp, Log, TEXT("sent msg len :: %d"), len);
		UE_LOG(LogTemp, Log, TEXT("@@@@ send fin"));
	}
};
