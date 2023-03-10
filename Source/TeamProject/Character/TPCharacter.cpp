// Fill out your copyright notice in the Description page of Project Settings.

#include "TPCharacter.h"
#include "CharacterStatComponent.h"


// Sets default values
ATPCharacter::ATPCharacter()
:
isSuper ( false ) 
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

	//머리 위 위젯 생성
	//FString path = "/Game/BP_UI/BP_Head";
	//LobbyUWClass = ConstructorHelpersInternal::FindOrLoadClass(path, ULogInUW::StaticClass());




	headUW = CreateDefaultSubobject<UWidgetComponent>(TEXT("HEADUW"));
	headUW->SetupAttachment(GetMesh());
	headUW->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	headUW->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/BP_UI/BP_Head"));
	if (UI_HUD.Succeeded())
	{
		headUW->SetWidgetClass(UI_HUD.Class);
		headUW->SetDrawSize(FVector2D(150.0f, 50.0f));
	}

	Time2 = 0.5f;
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

	UE_LOG(LogTemp, Log, TEXT("@@ATPCharacter::NotifyActorBeginOverlap() "));

	Time1 += DeltaTime;
	if (Time1 < Time2)
	{
		return;
	}

	Time1 = 0;

	TSet<AActor*> overlappedActors;
	this->GetOverlappingActors(overlappedActors);

	if (isSuper)
		return;
	for (auto otherActor : overlappedActors)
	{
		//충돌한 물체가 몬스터인지 검사
		AMonster* monster = Cast<AMonster>(otherActor);
		if (monster)
		{
			FVector monsterPos = otherActor->GetActorLocation();
			// Damage Process
			FVector testPlayerPos = this->GetActorLocation();

			UE_LOG(LogTemp, Log, TEXT("@@ATPCharacter::NotifyActorBeginOverlap() | is monster!!!!!!!!"));

			PacketManager& PacketManager = PacketManager::GetInstance();
			PacketManager.MakePMColliderRequestPacket(monsterPos);
		}

		ATPCharacter* character = Cast<ATPCharacter>(otherActor);
		if (character)
		{
			UE_LOG(LogTemp, Log, TEXT("@@ATPCharacter::NotifyActorBeginOverlap() | is character!!!!!!!!"));
			unsigned short characterIdx = character->GetIndex();
			//PacketManager& PacketManager = PacketManager::GetInstance();
			//PacketManager.MakePPColliderRequestPacket(characterIdx);
		}
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
		ChangeOpacity();
	}
}

void ATPCharacter::ChangeOpacity()
{
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(
		handle,    // TimerHandle
		FTimerDelegate::CreateLambda([this]()
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Timer"));
				// 깜빡이는거
			}),
		0.5f,
		true
	);

	FTimerHandle handle2;
	GetWorld()->GetTimerManager().SetTimer(
		handle2,    // TimerHandle
		FTimerDelegate::CreateLambda( [ this, handle ]() mutable
			{
				this->isSuper = false;

				GetWorld()->GetTimerManager().ClearTimer(handle);

			}),
		1.5f,
		false
	);
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
