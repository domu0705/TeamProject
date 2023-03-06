// Fill out your copyright notice in the Description page of Project Settings.

#include "SocketManager.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Internationalization/Text.h"
#include "Internationalization/Internationalization.h"


SocketManager::SocketManager()
{

}

SocketManager::~SocketManager()
{

}

/*
//서버로 데이터 전송 
void SocketManager::Send(FString& string)
{
	char message[BUFFER_SIZE];
	const wchar_t* encode = *string;
	char defaultSetting = '?';
	int32 len = WideCharToMultiByte(CP_ACP, 0, encode, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, encode, -1, message, len, &defaultSetting, NULL);
	int32 bytesSents = 0;


	bool IsSended = socket->Send((uint8*)(message), len, bytesSents);

	if (IsSended)
	{
		UE_LOG(LogTemp, Log, TEXT("Sended Message: %s"), *string);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to send message"));
	}
}
		*/

//로그인 요청

//지정된 주소로 연결
bool SocketManager::ConnectServer()
{
	socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket"));
	FString address = TEXT("127.0.0.1");
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(PORT);

	if (socket->Connect(*addr)) {
		isConnected = true;
		return true;
	}
	else
	{
		return false;
	}
}

//서버로부터 정보가 오는지 지속적 확인
void SocketManager::Tick()
{
	uint32 pendingSize = 0;
	if (!isConnected || !(socket->HasPendingData(pendingSize)))
		return;

	int curRecvBytes = 0;
	bool isReceived = socket->Recv(buffer + recvBytes, BUFFER_SIZE - recvBytes, curRecvBytes);

	if (isReceived)
	{
		recvBytes += curRecvBytes;

		if (curRecvBytes <= 0)
		{
			memset(buffer, 0, BUFFER_SIZE);
			recvBytes = 0;
			return;
		}

		//한글 받아지도록 변환
		FString recvStr = FString(UTF8_TO_TCHAR((const ANSICHAR*)buffer));

		if (recvStr.Contains("\r\n") == true)
		{
			TArray<FString> lines;
			recvStr.ParseIntoArray(lines, TEXT("\r\n"));
			if (lines.Num() > 0)
			{
				//불필요 데이터 삭제
				if (recvStr.Contains(TEXT("명령어안내")) == true)
				{
					TArray<FString> parsedStr;

					recvStr.ParseIntoArray(parsedStr, TEXT("명령어안내"));
					recvStr = parsedStr[0];
				}
				CheckRecvMsg(recvStr, lines[0]);
			}
		}
		memset(buffer, 0, BUFFER_SIZE);
		recvBytes = 0;
	}
}

//수신한 메시지 해석
void SocketManager::CheckRecvMsg(FString& recvStr, FString& str1)
{

}

void SocketManager::_sendPacket(Packet::PacketID packetType, void* packet)
{
	if (!packet)
	{
		return;
	}

	switch (packetType)
	{
	case Packet::PacketID::LOGINREQUEST:
	{
		Packet::LoginRequestPacket p = *(Packet::LoginRequestPacket*)(packet);
		int32 bytesSents = 0;
		socket->Send((uint8*)(packet), sizeof(p), bytesSents);
	}
	case Packet::PacketID::JOINROOMREQUEST:
	{
		Packet::JoinRoomRequestPacket p = *(Packet::JoinRoomRequestPacket*)(packet);
		int32 bytesSents = 0;
		socket->Send((uint8*)(packet), sizeof(p), bytesSents);
	}
	default:
	{
		break;
	}
	}
}

