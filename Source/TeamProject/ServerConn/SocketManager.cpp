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
	revcPacket();
}

void SocketManager::revcPacket()
{
	if (!isConnected)
		return;

	char buffer[BUFFER_SIZE];
	char* packet = savingBuffer;
	int32 curRecvBytes = 0;
	int32 packetSize = 0;

	bool isReceived = socket->Recv((uint8*)(buffer), BUFFER_SIZE - 1, curRecvBytes);
	if (!isReceived)
		return;
	
	// 받은 데이터 없음
	if (curRecvBytes == 0)
		return;

	//새로 받은 정보를 담은 buffer을 이전에 받은 정보들을 저장해둔 savingBuffer 에 저장, prevRecvBytes 는 savingBuffer가 얼마나 차있는지 인덱스임.
	//savingBuffer가 비어있다면 prevRecvBytes = 0;
	std::copy(buffer, buffer + curRecvBytes, savingBuffer + prevRecvBytes);

	do
	{
		// 받아올 패킷 크기 알기
		packetSize = packet[0];

		// 받아올 패킷 데이터 크기보다 받은 데이터가 많을 경우 -> 패킷을 조립해서 ProcessPacket 수행
		if (packetSize <= curRecvBytes)
		{
			//단 하나의 패킷
			char onePacket[BUFFER_SIZE] = { NULL, };

			//단 하나의 패킷 크키만큼 savingBuffer에서 onePacket으로 복사
			std::copy(savingBuffer, savingBuffer + packetSize, onePacket);

			//패킷 해석
			interpretPacket(onePacket);

			packet += packetSize;
			curRecvBytes -= packetSize;

			if (curRecvBytes != 0)
			{
				//savingBuffer 초기화를 위한 빈 버퍼
				char cleanBuffer[BUFFER_SIZE];

				//처리한 패킷 데이터를 savingBuffer에서 제외해 줌
				std::copy(packet, packet + BUFFER_SIZE, cleanBuffer);
				std::copy(cleanBuffer, cleanBuffer + BUFFER_SIZE, savingBuffer);
				packet = savingBuffer;
			}
			else
			{
				prevRecvBytes = 0;
				ZeroMemory(savingBuffer, sizeof(savingBuffer));
			}
		}
		// 패킷 데이터 크기가 받은 데이터보다 많음 -> 패킷을 더 받아야 함
		else
		{
			prevRecvBytes += curRecvBytes;
		}
	} while (curRecvBytes > 0);
}

//수신한 메시지 해석
void SocketManager::interpretPacket(char* packet)
{
	if (!packet)
		return;

	//패킷 구분자 가져오기 - packet 에서 앞에 패킷 크키(sizeof(unsigned short)) 다음에 오는 패킷 구분자를 가져옴
	Packet::PacketID packetID = *(Packet::PacketID*)(packet + sizeof(unsigned short));

	switch (packetID)
	{
	case Packet::PacketID::LOGINRESULT:
	{
		Packet::LoginResultPacket p = *reinterpret_cast<Packet::LoginResultPacket*> (packet);
		bool isLogInSuccess = p.LoginSuccess;

		if (isLogInSuccess)
		{
			UE_LOG(LogTemp, Log, TEXT("SocketManager::interpretPacket() | isLogInSuccess"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("SocketManager::interpretPacket() | isLogInfail"));
		}

	}
	break;
	//case ServerToClient::COLLISION_BLOCK:
	//{
	//	Packet::CollisionTile p = *reinterpret_cast<Packet::CollisionTile*>(packet);
	//	ActorManager::GetInstance().ChangeBottomColor(UserManager::GetInstance().GetCharacterColor(p.owner), p.tileIndex);
	//}

	//break;
	default:
		break;
	}

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