#include "Actors/Cell/CPP_Cell.h"
#include "Utils/FunctionLibraries/CPP_CellFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>
#include "Core/GameControllers/CPP_PlayerController.h"
#include "Characters/Player/CPP_Player.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"





ACPP_Cell::ACPP_Cell()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ACPP_Cell::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ACPP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	checkf(PlayerController, TEXT("***> No PlayerController (nullptr) <***"));
}


void ACPP_Cell::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);	
}

void ACPP_Cell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsCellMoving)
	{
		//MoveCell();
	}
}


//void ACPP_Cell::MoveCell()
//{
//	FVector RealLocation;
//	FRotator RealRotation;
//
//	UCPP_CellFunctionLibrary::CalculateWorldLocationRotationFromCenterCell(
//		PlayerController->GetFirstCell(), RelativeLocation, RealLocation, RealRotation);
//
//	SetActorLocation(RealLocation);
//	SetActorRotation(RealRotation);
//}


FVector2f ACPP_Cell::GetAxialLocation() const
{
	return AxialLocation;
}



FVector2D ACPP_Cell::GetRelativeLocation() const
{
	return RelativeLocation;
};



void ACPP_Cell::SetAxialLocation(FVector2f NewAxialLocation)
{
	AxialLocation = NewAxialLocation;
	SetRelativeLocation();
}



void ACPP_Cell::SetRelativeLocation()
{
	FVector2f OriginAxLocation { FVector2f(0, 0) };
	
	if (Player)
	{
		OriginAxLocation = Player->GetAxialLocation();
	}

	UCPP_CellFunctionLibrary::GetRelativeLocationFromAnOrigin(GridSettings->DistanceBetweenNeighbours,
		OriginAxLocation, AxialLocation, RelativeLocation);

	//MoveCellEventDelegate.Broadcast(true);
	//MoveCell();
}



