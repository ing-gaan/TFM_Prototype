#include "Actors/Cell/Components/CPP_AC_Cell_Movement.h"
#include "Utils/FunctionLibraries/CPP_FuncLib_CellUtils.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Utils/Macros/Macros.h"





void UCPP_AC_Cell_Movement::BeginPlay()
{
	Super::BeginPlay();
	RegisterEventFunctions();
	CurrentZLocation = GameSettings->CellsDefaultHeightFromGround;
}

void UCPP_AC_Cell_Movement::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterEventFunctions();
}

void UCPP_AC_Cell_Movement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



void UCPP_AC_Cell_Movement::RegisterEventFunctions() const
{
	OwnerCell->MoveCellEventDelegate.AddUniqueDynamic(
		this, &UCPP_AC_Cell_Movement::MoveCellEvent);
}


void UCPP_AC_Cell_Movement::UnRegisterEventFunctions() const
{
	OwnerCell->MoveCellEventDelegate.RemoveDynamic(
		this, &UCPP_AC_Cell_Movement::MoveCellEvent);
}



void UCPP_AC_Cell_Movement::InitComponent()
{
	Super::InitComponent();

	
}


void UCPP_AC_Cell_Movement::MoveCellEvent(bool bCellsMoving, bool bIsShifting)
{
	if (!bCellsMoving && !bIsShifting)
	{
		return;
	}


	FVector RealLocation;
	FRotator RealRotation;

	UCPP_FuncLib_CellUtils::CalculateWorldLocationRotationBasedOnPlayer(
		OwnerCell->Player, OwnerCell->GetRelativeLocation(), RealLocation, RealRotation);

	RealLocation.Z = CurrentZLocation;

	OwnerCell->SetActorLocation(RealLocation);
	OwnerCell->SetActorRotation(RealRotation);	
	
}

