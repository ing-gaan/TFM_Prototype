#include "Characters/Player/CPP_Player.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"



ACPP_Player::ACPP_Player()
{
	PrimaryActorTick.bCanEverTick = false;
}


void ACPP_Player::BeginPlay()
{
	Super::BeginPlay();

	SetAxialLocation(GridSettings->FirstAxialLocation);
	
}


void ACPP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACPP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


FVector2f ACPP_Player::GetAxialLocation() const
{
	return AxialLocation;
}



FVector2D ACPP_Player::GetRelativeLocation() const
{
	return RelativeLocation;
};



void ACPP_Player::SetAxialLocation(FVector2f NewAxialLocation)
{
	AxialLocation = NewAxialLocation;

	float Z = GameSettings->DefaultHeightFromGround;
	FVector HeightVector = FVector(0, 0, Z);

	SetActorLocation( GetActorLocation() + HeightVector );
}

