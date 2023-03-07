// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Manager/WarningBoxManager.h"
#include "PacketBox.generated.h"

UCLASS()
class TEAMPROJECT_API APacketBox : public AActor
{
	GENERATED_BODY()
private:
	bool isOn;
	WarningBoxManager* boxManager;
public:	
	// Sets default values for this actor's properties
	APacketBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyHit(UPrimitiveComponent*MyComp,AActor*Other,UPrimitiveComponent*OtherComp,bool bSelfMovved,FVector HitLocation ,
		FVector HitNormal,FVector NormalImpulse,const FHitResult& Hit) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

	UPROPERTY(EditAnyWhere)
		UStaticMeshComponent* BoxMesh;
};
