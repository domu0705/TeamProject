// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma pack(push,1)
enum class PacketID
{
	PLAY,
	SKILL,
	LOGIN,
	JOINROOM
};

enum class LoginPacketID
{
	SUCCESS,
	FAIL
};

enum class JoinRoom
{
	SUCCESS,
	FAIL
};

struct LoginPacket
{
	unsigned short packetSize;
	PacketID packetID;
	FString userID;
	LoginPacket(FString inUserID);
};

struct JoinRoomPacket
{
	int packetSize;
	PacketID packetID;
	FString roomName;
	JoinRoomPacket(FString inRoomName);
};
#pragma pack(pop)