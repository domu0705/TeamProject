#include "Packet.h"

namespace Packet
{
	LoginResultPacket::LoginResultPacket(bool In_LoginSuccess)
	{
		packetSize = sizeof(int) + sizeof(PacketID) + sizeof(bool);
		packetID = PacketID::LOGINRESULT;
		LoginSuccess = In_LoginSuccess;
	}

	JoinRoomResultPacket::JoinRoomResultPacket(bool In_JoinRoomSuccess)
	{
		packetSize = sizeof(int) + sizeof(PacketID) + sizeof(bool);
		packetID = PacketID::JOINROOMRESULT;
		JoinRoomSuccess = In_JoinRoomSuccess;
	}

	LoginRequestPacket::LoginRequestPacket(const FString& nickname)
	{
		packetSize = sizeof(unsigned short) + sizeof(PacketID) + PacketProtocol::NICKNAME_MAXSIZE;
		packetID = PacketID::LOGINREQUEST;
		// donghyun : char[] 
		LoginNickname[0] = { 0, };
		int32 CharArraySize = strlen(TCHAR_TO_UTF8(*nickname)) + 1;
		FCStringAnsi::Strncpy(LoginNickname, TCHAR_TO_UTF8(*nickname), CharArraySize);
	}
}