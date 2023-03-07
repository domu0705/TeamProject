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
#include <vector>
#include <string>


class ATPCharacter;

class TEAMPROJECT_API SocketManager
{
	enum
	{
		BUFFER_SIZE = 2048,
		PORT = 8080
	};

private:
	//클라이언트의 소켓
	FSocket* socket;
	//uint8 buffer[BUFFER_SIZE] = { 0 };
	char savingBuffer[BUFFER_SIZE];
	int recvBytes = 0;
	unsigned char prevRecvBytes= 0;

	//TArray<ATPCharacter*> characterAry;
	FString myID;
	ATPCharacter* myCharacter;
	TArray<ATPCharacter*> otherCharacterAry;
	TMap<int32, ATPCharacter*> characterAry;

public:
	static SocketManager& GetInstance()
	{
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
	//void CheckRecvMsg(FString& recvStr, FString& str1);
	void _sendPacket(Packet::PacketID packetType, void* packet);
	void revcPacket();
	void interpretPacket(char* packet);
	template< class PacketType >
	void sendPacket(const PacketType& packet)
	{
		int32 bytesSents = 0;
		socket->Send((uint8*)databuf.data(), databuf.size(), bytesSents);

		//int32 len = 0;// 계산 필요
		int32 bytesSents = 0;
		const FString packetStr(reinterpret_cast<const TCHAR*>(&packet));
		FTCHARToUTF8 Converter(*packetStr);
		const char* multiByteString = (const char*)Converter.Get();
		int32 len = FCStringAnsi::Strlen(multiByteString);
		socket->Send((uint8*)(multiByteString), len, bytesSents);
		UE_LOG(LogTemp, Log, TEXT("sent msg len :: %d"), bytesSents);
		UE_LOG(LogTemp, Log, TEXT("@@@@ send fin"));
	}

	const FString& GetMyID() { return myID; }
	void SetMyID(const FString& inMyID) { myID = inMyID; }
	ATPCharacter* getMyCharacter() { return myCharacter; }
	void SetMyCharacter(ATPCharacter* inCharacter) { myCharacter = inCharacter; }
	ATPCharacter* GetOtherCharacter(int32 num) { return otherCharacterAry[num]; }
	void SetOtherCharacter(ATPCharacter* inCharacter) { otherCharacterAry.Add(inCharacter); }
	TMap<int32, ATPCharacter*> GetCharacterAry() { return characterAry; }
	ATPCharacter* GetCharacterAry(int32 index) { return characterAry[index]; }
	void SetCharacterAry(int32 id, ATPCharacter* inCharacter) { characterAry.Add(id,inCharacter ); }
	bool GetIsConnected() { return isConnected; }
	//참고
	//AMiniGameCharacter* GetCharacter3() { return m_Character3; }
	//void SetCharacter3(AMiniGameCharacter* varCharacter) { m_Character3 = varCharacter; }
};