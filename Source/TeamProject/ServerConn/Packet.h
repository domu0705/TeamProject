#pragma once

namespace PacketProtocol
{
	constexpr unsigned short PACKET_MAXSIZE = 1024;
	constexpr unsigned short NICKNAME_MAXSIZE = 128;
	constexpr unsigned short BUF_MAXSIZE = 1024;
	constexpr unsigned short IP_MAXSIZE = 20;
}

#pragma pack(push,1)
namespace Packet
{
	enum class PacketID : unsigned char
	{
		PLAY,
		SKILL,
		LOGINREQUEST,
		LOGINRESULT,
		JOINROOMREQUEST,
		JOINROOMRESULT
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

	struct LoginResultPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		bool LoginSuccess;
		LoginResultPacket(bool In_LoginSuccess);
	};

	struct LoginRequestPacket
	{
		unsigned short packetSize;
		PacketID packetID;
		char LoginNickname[PacketProtocol::NICKNAME_MAXSIZE];
		LoginRequestPacket(const FString& nickname);
	};

	struct JoinRoomResultPacket
	{
		int packetSize;
		PacketID packetID;
		bool JoinRoomSuccess;
		JoinRoomResultPacket(bool In_JoinRoomSuccess);
	};

	struct JoinRoomRequestPacket
	{
		int packetSize;
		PacketID packetID;
		unsigned short RoomNum;
	};
}
#pragma pack(pop)