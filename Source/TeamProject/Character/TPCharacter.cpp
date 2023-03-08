// Fill out your copyright notice in the Description page of Project Settings.

#include "TPCharacter.h"
#include "CharacterStatComponent.h"

// Sets default values
ATPCharacter::ATPCharacter()
{
	UE_LOG(LogTemp, Log, TEXT("@@ATPCharacter::ATPCharacter()"));
 	// character가 매 프레임마다 Tick()을 호출. 꺼도 됨
	PrimaryActorTick.bCanEverTick = true;
	SetStat();

	//overlap확인을 위한 capsule component 생성
	overlapCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSUPECOMPONENT"));
	overlapCapsule->InitCapsuleSize(75.f, 96.f);
	overlapCapsule->SetCollisionProfileName(FName("PlayerOverlap"));
	overlapCapsule->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATPCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (nickName == TEXT("myCharacter"))
	{
		UE_LOG(LogTemp, Log, TEXT("@@ATPCharacter::BeginPlay() | Set myCharacter"));
		SocketManager::GetInstance().SetMyCharacter(this);
	}
	else 
	{
		UE_LOG(LogTemp, Log, TEXT("@@ATPCharacter::BeginPlay() | Set other Character"));
		SocketManager::GetInstance().SetOtherCharacter(this);
	}

}

// Called every frame
void ATPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATPCharacter::NotifyActorBeginOverlap(AActor* OtherActor)//collision preset ->overlapall로 변경
{
	UE_LOG(LogTemp, Log, TEXT("@@ATPCharacter::NotifyActorBeginOverlap() "));
	//충돌한 물체가 몬스터인지 검사
	AMonster* monster = Cast<AMonster>(OtherActor);
	if (monster)
	{
		FVector monsterPos = OtherActor->GetActorLocation();
		// Damage Process
		FVector testPlayerPos = this->GetActorLocation();
		UE_LOG(LogTemp, Log, TEXT("@@ATPCharacter::NotifyActorBeginOverlap() | is monster!!!!!!!!"));
		PacketManager& PacketManager = PacketManager::GetInstance();
		PacketManager.MakePMColliderRequestPacket(monsterPos);
	}

	ATPCharacter* character = Cast<ATPCharacter>(OtherActor);
	if (character)
	{
		UE_LOG(LogTemp, Log, TEXT("@@ATPCharacter::NotifyActorBeginOverlap() | is character!!!!!!!!"));
		unsigned short characterIdx = character->GetIndex();
		PacketManager& PacketManager = PacketManager::GetInstance();
		PacketManager.MakePPColliderRequestPacket(characterIdx);
	}
}
// Called to bind functionality to input
void ATPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATPCharacter::SetStat()
{
	MaxHP = 3;
	CurrentHP = MaxHP;
	isSuper = false;
	superDuration = 2;
}
/*
void ATPCharacter::MovePosition()
{
	// Get a reference to the player character
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// Set the new location for the player
	FVector newLocation = FVector(100.0f, 0.0f, 0.0f);
	playerCharacter->SetActorLocation(newLocation);
}
*/

void ATPCharacter::GetDamage()
{
	UE_LOG(LogTemp, Log, TEXT("ATPCharacter::GetDamage()"));
	if (isSuper)
		return;

	if (CurrentHP <= 1)//죽음
	{
		UE_LOG(LogTemp, Log, TEXT("ATPCharacter::GetDamage() | Current HEalth = %d -> Do die"), CurrentHP);
	}
	else//생명 감소
	{
		--CurrentHP;
		UE_LOG(LogTemp, Log, TEXT("Current HEalth = %d"), CurrentHP);
		isSuper = true;
		UpdateHP();
	}
}

void ATPCharacter::UpdateHP()
{
	UserWidgetManager* UserWidgetManager = UserWidgetManager::GetInstance();
	if (!UserWidgetManager)
		return;
	UserWidgetManager->UpdateHP(CurrentHP);
}

void ATPCharacter::SetIndex(unsigned short inIndex)
{
	index = inIndex;
}

unsigned short ATPCharacter::GetIndex()
{
	return index;
}
