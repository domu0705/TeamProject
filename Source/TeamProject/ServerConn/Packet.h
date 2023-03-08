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
	// donghyun : ms ����
	constexpr unsigned int TIMER_UPDATE_PERIOD = 1000;
	constexpr unsigned int TASK_UPDATE_PERIOD = 50;
	constexpr unsigned int RANDNUM_SEEDRANGE = 1000;
	constexpr unsigned int GAMEMAP_SIZE = 7;
	// donghyun : 0��° position ������ ���X
	constexpr float PLAYER_INITPOS[5][3] = { {100.0f, -100.0f, 140.0f},
										   {100.0f, 100.0f, 140.0f},
										   {-100.0f, -100.0f, 140.0f},
										   {-100.0f, 100.0f, 140.0f},
										   {0.0f, 0.0f, 140.0f} };
	constexpr float PLAYER_COLLIDER_RADIUS = 75.0f;
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
		PMCOLLIDERESULT,
		PPCOLLIDERESULT,
		// client -> server
		UPDATE,
		LOGINREQUEST,
		MAKEROOMREQUEST,
		JOINROOMREQUEST,
		PMCOLLIDEREQUEST,
		PPCOLLIDEREQUEST,
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
		PlayPacket(unsigned short InfoMapIdx);
	};

	struct SpawnPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		// donghyun : row idx, ��� 1~7
		unsigned short rowIdx;
		// donghyun : col idx, ��� 1~7
		unsigned short colIdx;
		// donghyun : true�� ����(����) or ����(����), False�� ������(����) or �Ʒ���(����)
		unsigned short directionIdx;
		SpawnPacket(bool in_IsHorizontal, unsigned short in_lineIdx, bool in_directionFlag);
	};

	// donghyun : GameStartPacket ���� ���ԵǴ� ���� �÷��̾� ���� ����ü
	struct PlayerInfo
	{
		unsigned short playerIdx;
		char nickName[PacketProtocol::NICKNAME_MAXSIZE];
		float posVec[3];
		float rotVec[3];
		PlayerInfo() {}
		PlayerInfo(unsigned short in_playerIdx, const char* in_nickName, const float* in_posVec, const float* in_rotvec);
		PlayerInfo(const PlayerInfo& in_playerInfo);

		static unsigned short getPlayerInfoByteSize();
	};

	// donghyun : ���� ���� �� �� �÷��̾��� ������ �˷��ִ� ��Ŷ
	struct GameStartPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		PlayerInfo playerInfo;
		GameStartPacket(const PlayerInfo& in_playerInfo);
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
		// TODO : ������ ����
		//MakeRoomResultPacket();
	};

	struct JoinRoomResultPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		bool JoinRoomSuccess;
		JoinRoomResultPacket(bool In_JoinRoomSuccess);
	};

	struct TimerPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		unsigned short timeSecond;
		TimerPacket(unsigned short in_timeSecond);
	};

	// donghyun : ��-��, ��-�� ��ο� ���� �浹 ��� ��Ŷ
	struct CollideResultPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		bool IsCollided;
		float forceDir[3];
		CollideResultPacket(const bool in_IsCollided, const float* in_forceDir);
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
		unsigned short packetSize;
		PacketID packetID;
		unsigned short RoomNum;
	};

	struct PMColliderRequestPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		float monsterPos[3];
		PMColliderRequestPacket(float* inMonsterPos);
	};

	struct PPColliderRequestPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		unsigned short oppoPlayerIdx;
		PPColliderRequestPacket(unsigned short inOppoPlayerIdx);
	};
}
#pragma pack(pop)