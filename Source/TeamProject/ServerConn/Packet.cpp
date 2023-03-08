#include "Packet.h"

namespace Packet
{
	//서버
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

	PlayPacket::PlayPacket(int InfoMapIdx)
	{
		packetSize = sizeof(unsigned short) + sizeof(PacketID) + sizeof(unsigned short) + (sizeof(float) * 6);
		packetID = PacketID::PLAY;
		playerIdx = InfoMapIdx;
		posVec[0] = { 0.0f, };
		rotVec[0] = { 0.0f, };
	}

	PlayerInfo::PlayerInfo(unsigned short in_playerIdx, char* in_nickName, float* in_posVec, float* in_rotvec)
	{
		playerIdx = in_playerIdx;
		memcpy_s(&playerIdx, PacketProtocol::NICKNAME_MAXSIZE, in_nickName, strlen(in_nickName));
		for (int i = 0; i < 3; ++i)
		{
			posVec[i] = in_posVec[i];
			rotVec[i] = in_rotvec[i];
		}
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
}