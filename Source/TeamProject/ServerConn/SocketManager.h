// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include <locale.h>

class TEAMPROJECT_API SocketManager
{
	enum
	{
		BUFFER_SIZE = 2048,
		PORT = 8080
	};

private:
	FSocket* socket;
	uint8 buffer[BUFFER_SIZE] = { 0 };
	int recvBytes = 0;
public:
	static SocketManager* GetInstance() {
		static SocketManager s;
		return &s;
	}

	bool isConnected;

	SocketManager();
	~SocketManager();

	void Tick();
	bool ConnectServer();
	void Send(FString& string);
	void SendLogin(const FString& name);
	void CheckRecvMsg(FString& recvStr, FString& str1);
};
