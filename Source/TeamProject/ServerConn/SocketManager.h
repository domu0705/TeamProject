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
	
	//충돌하면 날라가는 힘
	float colWithMonsterPower;
	float colWithPlayerPower;

	//TArray<ATPCharacter*> characterAry;
	FString myID;
	ATPCharacter* myCharacter;
	TArray<ATPCharacter*> otherCharacterAry;
	TMap<unsigned short, ATPCharacter*> characterAry;

public:
	static SocketManager& GetInstance()
	{
		static SocketManager i;
		return i;
	}
	int32 testIdx = 0;
	bool isConnected;

	SocketManager();
	~SocketManager();
	int32 curOtherCharacterNum;
	void Init();
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
	//내 캐릭터 가져오기
	ATPCharacter* getMyCharacter() { return myCharacter; }
	void SetMyCharacter(ATPCharacter* inCharacter) { myCharacter = inCharacter; }
	//내 캐릭터를 제외한, 시작 전 비어있는 캐릭터 중 하나 반환
	ATPCharacter* GetOtherCharacter(int32 num) { return otherCharacterAry[num]; }
	void SetOtherCharacter(ATPCharacter* inCharacter) { otherCharacterAry.Add(inCharacter); }
	TMap<unsigned short, ATPCharacter*> GetCharacterAry() { return characterAry; }
	ATPCharacter* GetCharacterAry(unsigned short index) { return characterAry[index]; }
	void SetCharacterAry(int32 id, ATPCharacter* inCharacter) { characterAry.Add(id,inCharacter ); }
	bool GetIsConnected() { return isConnected; }
};