// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TEAMPROJECT_API PacketManager
{
public:
	static PacketManager& GetInstance() {
		static PacketManager i;
		return i;
	}

	PacketManager();
	~PacketManager();

	void SendLogin(const FString& inID);
};
