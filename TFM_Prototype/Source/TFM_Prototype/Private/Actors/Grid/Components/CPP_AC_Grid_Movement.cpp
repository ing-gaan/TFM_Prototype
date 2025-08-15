#include "Actors/Grid/Components/CPP_AC_Grid_Movement.h"
#include "Actors/Grid/CPP_Grid.h"
#include "Utils/FunctionLibraries/CPP_FuncLib_CellUtils.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Characters/Player/CPP_Player.h"
#include "Utils/Macros/Macros.h"




void UCPP_AC_Grid_Movement::BeginPlay()
{
	Super::BeginPlay();
	RegisterEventFunctions();
	CurrentZLocation = GameSettings->HiddenHeightFromGround;
}

void UCPP_AC_Grid_Movement::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterEventFunctions();
}

void UCPP_AC_Grid_Movement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



void UCPP_AC_Grid_Movement::RegisterEventFunctions() const
{
	OwnerGrid->MoveGridEventDelegate.BindDynamic(this, &UCPP_AC_Grid_Movement::MoveGridEvent);
}


void UCPP_AC_Grid_Movement::UnRegisterEventFunctions() const
{
	OwnerGrid->MoveGridEventDelegate.Clear();
}



void UCPP_AC_Grid_Movement::InitComponent()
{
	Super::InitComponent();
}


void UCPP_AC_Grid_Movement::MoveGridEvent(bool bCellsMoving)
{
	if (!bCellsMoving)
	{
		return;
	}

	FVector RealLocation = OwnerGrid->Player->GetActorLocation();
	FRotator RealRotation = OwnerGrid->Player->GetActorRotation();

	RealLocation.Z = OwnerGrid->GetActorLocation().Z;

	OwnerGrid->SetActorLocation(RealLocation);
	OwnerGrid->SetActorRotation(RealRotation);
}