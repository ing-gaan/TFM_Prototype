#include "Characters/Player/CPP_Player.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Components/SphereComponent.h"



ACPP_Player::ACPP_Player()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));	
	SphereCollision->SetupAttachment(RootComponent);	
	SphereCollision->SetSphereRadius(10);
}


void ACPP_Player::BeginPlay()
{
	Super::BeginPlay();

	InitPlayer();
	SetAxialLocation(GridSettings->FirstAxialLocation);

}


void ACPP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void ACPP_Player::InitPlayer()
{
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;
	GridSettings = GameSettings->GridSettings;	

	
}



FVector2f ACPP_Player::GetAxialLocation() const
{
	return AxialLocation;
}



FVector2D ACPP_Player::GetRelativeLocation() const
{
	return RelativeLocation;
}


void ACPP_Player::SetSphereCollisionRadius(int Radius)
{
	SphereCollision->SetSphereRadius(Radius);
}



void ACPP_Player::SetAxialLocation(FVector2f NewAxialLocation)
{
	AxialLocation = NewAxialLocation;
	
	FVector PlayerLocation = GetActorLocation();
	PlayerLocation.Z = GameSettings->CellsDefaultHeightFromGround;
	SetActorLocation(PlayerLocation);
}
