#include "Packet.h"

namespace Packet
{
	LoginResultPacket::LoginResultPacket(bool In_LoginSuccess)
	{
		packetSize = sizeof(unsigned short) + sizeof(PacketID) + sizeof(bool);
		packetID = PacketID::LOGINRESULT;
		LoginSuccess = In_LoginSuccess;
	}

	JoinRoomResultPacket::JoinRoomResultPacket(bool In_JoinRoomSuccess)
	{
		packetSize = sizeof(unsigned short) + sizeof(PacketID) + sizeof(bool);
		packetID = PacketID::JOINROOMRESULT;
		JoinRoomSuccess = In_JoinRoomSuccess;
	}

	PlayPacket::PlayPacket(unsigned short InfoMapIdx)
	{
		packetSize = sizeof(unsigned short) + sizeof(PacketID) + sizeof(unsigned short) + (sizeof(float) * 6);
		packetID = PacketID::PLAY;
		playerIdx = InfoMapIdx;
		posVec[0] = { 0.0f, };
		rotVec[0] = { 0.0f, };
	}

	PlayerInfo::PlayerInfo(unsigned short in_playerIdx, const char* in_nickName, const float* in_posVec, const float* in_rotvec)
	{
		nickName[0] = { 0, };
		playerIdx = in_playerIdx;
		//memcpy_s(&playerIdx, PacketProtocol::NICKNAME_MAXSIZE, in_nickName, strlen(in_nickName));
		strcpy_s(nickName, PacketProtocol::NICKNAME_MAXSIZE, in_nickName);
		for (int i = 0; i < 3; ++i)
		{
			posVec[i] = in_posVec[i];
			rotVec[i] = in_rotvec[i];
		}
	}

	PlayerInfo::PlayerInfo(const PlayerInfo& in_playerInfo)
	{
		// 복사 생성자
		playerIdx = in_playerInfo.playerIdx;
		strcpy_s(nickName, PacketProtocol::NICKNAME_MAXSIZE, in_playerInfo.nickName);
		for (int i = 0; i < 3; ++i)
		{
			posVec[i] = in_playerInfo.posVec[i];
			rotVec[i] = in_playerInfo.rotVec[i];
		}
	}

	unsigned short PlayerInfo::getPlayerInfoByteSize()
	{
		return sizeof(unsigned short) + PacketProtocol::NICKNAME_MAXSIZE + sizeof(float) * 6;
	}

	GameStartPacket::GameStartPacket(const PlayerInfo& in_playerInfo)
	{
		packetSize = sizeof(unsigned short) + sizeof(PacketID) + PlayerInfo::getPlayerInfoByteSize();
		packetID = PacketID::GAMESTART;
		playerInfo = in_playerInfo;
	}

	TimerPacket::TimerPacket(unsigned short in_timeSecond)
	{
		packetSize = sizeof(unsigned short) + sizeof(PacketID) + sizeof(unsigned short);
		packetID = PacketID::TIMER;
		timeSecond = in_timeSecond;
	}

	SpawnPacket::SpawnPacket(bool in_IsHorizontal, unsigned short in_lineIdx, bool in_directionFlag)
	{
		packetSize = sizeof(unsigned short) + sizeof(PacketID) + (sizeof(unsigned short) * 3);
		packetID = PacketID::SPAWN;
		rowIdx = in_IsHorizontal ? in_lineIdx : 0;
		colIdx = in_IsHorizontal ? 0 : in_lineIdx;
		directionIdx = in_directionFlag ? 0 : 1;
	}

	CollideResultPacket::CollideResultPacket(const bool in_IsCollided, const float* in_forceDir)
	{
		packetSize = sizeof(unsigned short) + sizeof(PacketID) + sizeof(bool) + (sizeof(float) * 3);
		packetID = PacketID::PMCOLLIDERESULT;
		IsCollided = in_IsCollided;
		for (int i = 0; i < 3; i++)
		{
			forceDir[i] = in_forceDir[i];
		}
	}

	//////////
	// 클라 //
	//////////
	UpdatePacket::UpdatePacket(float* inPosVec, float* inRotVec)
	{
		packetSize = sizeof(unsigned short) + sizeof(PacketID) + (sizeof(float) * 6);
		packetID = PacketID::UPDATE;
		for (int i = 0; i < 3; ++i)
		{
			posVec[i] = inPosVec[i];
			rotVec[i] = inRotVec[i];
		}
	}

	LoginRequestPacket::LoginRequestPacket(const FString& nickname)
	{
		packetSize = sizeof(unsigned short) + sizeof(PacketID) + PacketProtocol::NICKNAME_MAXSIZE;
		packetID = PacketID::LOGINREQUEST;
		// donghyun : char[] �ʱ�ȭ
		LoginNickname[0] = { 0, };
		int32 CharArraySize = strlen(TCHAR_TO_UTF8(*nickname)) + 1;
		FCStringAnsi::Strncpy(LoginNickname, TCHAR_TO_UTF8(*nickname), CharArraySize);
	}

	PMColliderRequestPacket::PMColliderRequestPacket(float* inMonsterPos)
	{
		packetSize = sizeof(unsigned short) + sizeof(PacketID) + (sizeof(float) * 3);
		packetID = PacketID::PMCOLLIDEREQUEST;

		for (int i = 0; i < 3; i++)
		{
			monsterPos[i] = inMonsterPos[i];
		}
	};

	PPColliderRequestPacket::PPColliderRequestPacket(unsigned short inOppoPlayerIdx)
	{
		packetSize = sizeof(unsigned short) + sizeof(PacketID) + sizeof(unsigned short);
		packetID = PacketID::PPCOLLIDEREQUEST;
		oppoPlayerIdx = inOppoPlayerIdx;
	}
}