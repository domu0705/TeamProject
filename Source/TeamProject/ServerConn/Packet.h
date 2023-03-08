#pragma once
namespace PacketProtocol
{
	constexpr unsigned short PACKET_MAXSIZE = 1024;
	constexpr unsigned short NICKNAME_MAXSIZE = 32;
	constexpr unsigned short BUF_MAXSIZE = 1024;
	constexpr unsigned short IP_MAXSIZE = 20;
}
namespace ServerProtocol
{
	constexpr unsigned short ROOMNAME_MAXSIZE = 32;
}
#pragma pack(push,1)
namespace Packet
{
	enum class PacketID : unsigned char
	{
		// server -> client
		PLAY,
		SPAWN,
		GAMESTART,
		LOGINRESULT,
		MAKEROOMRESULT,
		JOINROOMRESULT,
		TIMER,
		// client -> server
		UPDATE,
		LOGINREQUEST,
		MAKEROOMREQUEST,
		JOINROOMREQUEST,
	};

	enum class LoginPacketID : unsigned char
	{
		SUCCESS,
		FAIL
	};

	enum class JoinRoom : unsigned char
	{
		SUCCESS,
		FAIL
	};

	// server -> client
	struct PlayPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		unsigned short playerIdx;
		float posVec[3];
		float rotVec[3];
		PlayPacket(int InfoMapIdx);
	};

	struct SpawnPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		// donghyun : true면 수평 방향, 아니면 수직 방향
		// donghyun : row idx, 모두 1~7
		unsigned short rowIdx;
		// donghyun : col idx, 모두 1~7
		unsigned short colIdx;
		// donghyun : true면 왼쪽(수평) or 위쪽(수직), False면 오른쪽(수평) or 아래쪽(수직)
		unsigned short directionIdx;
		SpawnPacket(bool in_IsHorizontal, unsigned short in_lineIdx, bool in_directionFlag);
	};

	// donghyun : GameStartPacket 내에 포함되는 개별 플레이어 정보 구조체
	struct PlayerInfo
	{
		unsigned short playerIdx;
		char nickName[PacketProtocol::NICKNAME_MAXSIZE];
		float posVec[3];
		float rotVec[3];
		PlayerInfo(unsigned short in_playerIdx, char* in_nickName, float* in_posVec, float* in_rotvec);
	};

	// donghyun : 게임 시작 전 각 플레이어의 정보를 알려주는 패킷
	struct GameStartPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		PlayerInfo playerArr;
		GameStartPacket();
	};

	struct LoginResultPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		bool LoginSuccess;
		LoginResultPacket(bool In_LoginSuccess);
	};

	struct MakeRoomResultPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		char roomName[ServerProtocol::ROOMNAME_MAXSIZE];
		//MakeRoomResultPacket();
	};

	struct JoinRoomResultPacket
	{
		int packetSize;
		PacketID packetID;
		bool JoinRoomSuccess;
		JoinRoomResultPacket(bool In_JoinRoomSuccess);
	};

	struct TimerPacket
	{
		int packetSize;
		PacketID packetID;
		unsigned short timeSecond;
		TimerPacket(unsigned short in_timeSecond);
	};

	/////////////////////
	// client -> server//
	/////////////////////
	struct UpdatePacket
	{
		unsigned short packetSize;
		PacketID packetID;
		float posVec[3];
		float rotVec[3];
		UpdatePacket(float* inPosVec, float* inRotVec);
	};

	struct LoginRequestPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		char LoginNickname[PacketProtocol::NICKNAME_MAXSIZE];
		// 클라
		LoginRequestPacket(const FString& nickname);
	};

	struct MakeRoomRequestPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		char LoginNickname[PacketProtocol::NICKNAME_MAXSIZE];
	};

	struct JoinRoomRequestPacket
	{
		int packetSize;
		PacketID packetID;
		unsigned short RoomNum;
	};
}
#pragma pack(pop)