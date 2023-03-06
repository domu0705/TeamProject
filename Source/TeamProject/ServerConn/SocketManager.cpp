#include "SocketManager.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Internationalization/Text.h"
#include "Internationalization/Internationalization.h"
#include "../Character/TPCharacter.h"

SocketManager::SocketManager()
{

}

SocketManager::~SocketManager()
{

}

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

	if (!isReceived)
		return;

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

		UE_LOG(LogTemp, Log, TEXT("sent msg len :: %d"), bytesSents);
		UE_LOG(LogTemp, Log, TEXT("@@@@ send fin"));

		break;
	}
	case Packet::PacketID::JOINROOMREQUEST:
	{
		Packet::JoinRoomRequestPacket p = *(Packet::JoinRoomRequestPacket*)(packet);
		int32 bytesSents = 0;
		socket->Send((uint8*)(packet), sizeof(p), bytesSents);

		UE_LOG(LogTemp, Log, TEXT("sent msg len :: %d"), bytesSents);
		UE_LOG(LogTemp, Log, TEXT("@@@@ send fin"));

		break;
	}
	default:
	{
		break;
	}
	}
}