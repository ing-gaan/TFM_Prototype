#include "Actors/Cell/Components/CPP_AC_Cell_Movement.h"
#include "Utils/FunctionLibraries/CPP_CellFunctionLibrary.h"
#include "Actors/Cell/CPP_Cell.h"





void UCPP_AC_Cell_Movement::BeginPlay()
{
	Super::BeginPlay();
	RegisterEventFunctions();
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
	OwnerCell->MoveCellEventDelegate.BindDynamic(this, &UCPP_AC_Cell_Movement::MoveCellEvent);
}


void UCPP_AC_Cell_Movement::UnRegisterEventFunctions() const
{
	OwnerCell->MoveCellEventDelegate.Clear();
}



void UCPP_AC_Cell_Movement::InitComponent()
{
	Super::InitComponent();

	
}


void UCPP_AC_Cell_Movement::MoveCellEvent()
{
	FVector RealLocation;
	FRotator RealRotation;

	UCPP_CellFunctionLibrary::CalculateWorldLocationRotationBasedOnPlayer(
		OwnerCell->Player, OwnerCell->GetRelativeLocation(), RealLocation, RealRotation);

	OwnerCell->SetActorLocation(RealLocation);
	OwnerCell->SetActorRotation(RealRotation);
}

