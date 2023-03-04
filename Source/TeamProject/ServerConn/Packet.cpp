// Fill out your copyright notice in the Description page of Project Settings.


#include "Packet.h"

LoginPacket::LoginPacket(FString inUserID)
{
	packetSize = sizeof(int) + sizeof(PacketID) + sizeof(FString);
	packetID = PacketID::LOGIN;
	userID = inUserID;
}

JoinRoomPacket::JoinRoomPacket(FString inRoomName)
{
	packetSize = sizeof(int) + sizeof(PacketID) + sizeof(bool);
	packetID = PacketID::JOINROOM;
	roomName = inRoomName;
}