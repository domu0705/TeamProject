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

	// 클라

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