// Fill out your copyright notice in the Description page of Project Settings.


#include "PacketBox.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/TPCharacter.h"

// Sets default values
APacketBox::APacketBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isOn = false;
	boxManager = WarningBoxManager::GetInstance();


	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	RootComponent = BoxMesh;
}

// Called when the game starts or when spawned
void APacketBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APacketBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APacketBox::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMovved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if (isOn)
		return;
	UE_LOG(LogTemp, Log, TEXT("APacketBox::NotifyHit"));
	boxManager->TurnOnBoxes(0, 3, 0); //테스트용. 지금은 이거 여러번 불림
	boxManager->TurnOnBoxes(2, 0, 1);
	boxManager->TurnOnBoxes(0, 5, 0);

	//진짜 내 로컬 플레이어를 가져오는지, 다른 클라 플레이어 가져오는지 확인해야 함.
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ATPCharacter* player = Cast<ATPCharacter>(playerCharacter);
	player->GetDamage();
	isOn = true;
}
