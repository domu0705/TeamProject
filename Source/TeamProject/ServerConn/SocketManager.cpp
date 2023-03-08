#include "SocketManager.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Internationalization/Text.h"
#include "Internationalization/Internationalization.h"
#include "../Character/TPCharacter.h"
#include "../Core/Timer.h"
#include "../Manager/WarningBoxManager.h"

SocketManager::SocketManager()
{

}

SocketManager::~SocketManager()
{
}

void SocketManager::Init()
{
	otherCharacterAry.Empty();
	characterAry.Empty();
	curOtherCharacterNum = 0;
}

void EndPlay();
//지정된 주소로 연결
bool SocketManager::ConnectServer()
{
	socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket"));
	socket->SetNonBlocking();
	socket->SetNoDelay();

	FString address = TEXT("127.0.0.1");//TEXT("172.28.35.237");
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(PORT);

	if (socket->Connect(*addr)) {
		socket->SetNonBlocking();
		socket->SetNoDelay();
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
		packetSize = *(unsigned short*)(packet);
		//packetSize = packet[0];

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
	case Packet::PacketID::LOGINRESULT://로그인 결과
	{
		Packet::LoginResultPacket p = *reinterpret_cast<Packet::LoginResultPacket*> (packet);
		bool isLogInSuccess = p.LoginSuccess;

		if (isLogInSuccess)
		{
			UE_LOG(LogTemp, Log, TEXT("!!!!!!!!!!!SocketManager::interpretPacket() | isLogInSuccess"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("!!!!!!!!!!!SocketManager::interpretPacket() | isLogInfail"));
		}

	}
	break;
	case Packet::PacketID::GAMESTART://인원수가 충분히 모였을 시 게임 시작
	{
		//UE_LOG(LogTemp, Log, TEXT("!!!!!!!!!!!SocketManager::interpretPacket() | GAMESTART"));
		Packet::GameStartPacket p = *reinterpret_cast<Packet::GameStartPacket*> (packet);
		/**/
		Packet::PlayerInfo playerAry = p.playerArr;
		FString nickName = FString(UTF8_TO_TCHAR(playerAry.nickName));
		
		if (nickName == SocketManager::GetInstance().GetMyID())
		{
			SocketManager::GetInstance().SetCharacterAry(p.playerArr.playerIdx, SocketManager::GetInstance().getMyCharacter());

			FVector rotVec = FVector(p.playerArr.rotVec[0], p.playerArr.rotVec[1], p.playerArr.rotVec[2]);
			FRotator rotFromVec = rotVec.Rotation();
			SocketManager::GetInstance().getMyCharacter()->SetActorLocation(FVector(p.playerArr.posVec[0], p.playerArr.posVec[1], p.playerArr.posVec[2]));
			auto loc = SocketManager::GetInstance().getMyCharacter()->GetActorLocation();
			SocketManager::GetInstance().getMyCharacter()->SetActorRotation(rotFromVec);
		}
		else 
		{
			ATPCharacter* newCharacter = SocketManager::GetInstance().GetOtherCharacter(curOtherCharacterNum);
			SocketManager::GetInstance().SetCharacterAry(p.playerArr.playerIdx, newCharacter);
			FVector rotVec = FVector(p.playerArr.rotVec[0], p.playerArr.rotVec[1], p.playerArr.rotVec[2]);
			FRotator rotFromVec = rotVec.Rotation();
			newCharacter->SetActorLocation(FVector(p.playerArr.posVec[0], p.playerArr.posVec[1], p.playerArr.posVec[2]));
			newCharacter->SetActorRotation(rotFromVec);
			++curOtherCharacterNum;
		}
		
	}
	break;
	case Packet::PacketID::PLAY://타 플레이어 위치 동기화
	{
		UE_LOG(LogTemp, Log, TEXT("@@ SocketManager::interpretPacket() | PLAY index = %d "), testIdx);
		++testIdx;
		Packet::PlayPacket p = *reinterpret_cast<Packet::PlayPacket*> (packet);
		ATPCharacter* movedCharacter = SocketManager::GetInstance().GetCharacterAry(p.playerIdx);
		if (!movedCharacter)
			return;
		movedCharacter->SetActorLocation(FVector(p.posVec[0], p.posVec[1], p.posVec[2]));
		FVector rotVec = FVector(p.rotVec[0], p.rotVec[1], p.rotVec[2]);

		FRotator rotFromVec = rotVec.Rotation();
		movedCharacter->SetActorRotation(rotFromVec);
	}
	break;
	case Packet::PacketID::SPAWN://투왕 스폰
	{
		//UE_LOG(LogTemp, Log, TEXT("!!!!!!!!!!!SocketManager::interpretPacket() | SPAWN"));
		Packet::SpawnPacket p = *reinterpret_cast<Packet::SpawnPacket*> (packet);
		WarningBoxManager::GetInstance().TurnOnBoxes((int32)(p.colIdx), (int32)(p.rowIdx), (int32)(p.directionIdx));
		//알맞은 스포너 활성화

	}
	break;
	case Packet::PacketID::TIMER://서버 시간 받아오기
	{
		//UE_LOG(LogTemp, Log, TEXT("!!!!!!!!!!!SocketManager::interpretPacket() | TIMER"));
		Packet::TimerPacket p = *reinterpret_cast<Packet::TimerPacket*> (packet);
		Timer::GetInstance().SetTime((int32)(p.timeSecond));
	}
	break;
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
	case Packet::PacketID::UPDATE:
	{
		Packet::UpdatePacket p = *(Packet::UpdatePacket*)(packet);
		int32 bytesSents = 0;
		socket->Send((uint8*)(packet), sizeof(p), bytesSents);

		//UE_LOG(LogTemp, Log, TEXT("sent msg len :: %d"), bytesSents);

		break;
	}
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