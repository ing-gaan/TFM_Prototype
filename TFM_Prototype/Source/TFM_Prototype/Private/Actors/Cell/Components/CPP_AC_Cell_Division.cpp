#include "Actors/Cell/Components/CPP_AC_Cell_Division.h"
#include "Utils/FunctionLibraries/CPP_CellFunctionLibrary.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Utils/Macros/Macros.h"






void UCPP_AC_Cell_Division::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterEventFunctions();
}


void UCPP_AC_Cell_Division::InitComponent()
{
	Super::InitComponent();
	RegisterEventFunctions();
}


void UCPP_AC_Cell_Division::RegisterEventFunctions() const
{
	OwnerCell->DivideEventDelegate.BindDynamic(this, &UCPP_AC_Cell_Division::DivideEvent);
}


void UCPP_AC_Cell_Division::UnRegisterEventFunctions() const
{
	OwnerCell->DivideEventDelegate.Clear();
}



ACPP_Cell* UCPP_AC_Cell_Division::DivideEvent(FVector2f AxialLocation)
{
	float Distance = GridSettings->DistanceBetweenNeighbours;
	FVector2f OriginAxLoc = FVector2f::Zero();
	FVector2D RelativeLoc;
	UCPP_CellFunctionLibrary::GetRelativeLocationFromAnOrigin(Distance, OriginAxLoc, AxialLocation, RelativeLoc);

	FVector Location;
	Location.X = RelativeLoc.X;
	Location.Y = RelativeLoc.Y;
	Location.Z = GameSettings->DefaultHeightFromGround;
	FRotator Rotation = FRotator::ZeroRotator;
	TSubclassOf<ACPP_Cell> CellClass = OwnerCell->GetClass();

	ACPP_Cell* NewCell = SpawnCell(Location, Rotation, CellClass);
	ConfigureNewCell(NewCell, AxialLocation);

	return NewCell;
}


ACPP_Cell* UCPP_AC_Cell_Division::SpawnCell(FVector CellLocation, FRotator CellRotation, TSubclassOf<ACPP_Cell> CellClass)
{
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ACPP_Cell* CellSpawned = GetWorld()->SpawnActor<ACPP_Cell>(CellClass, CellLocation, CellRotation, SpawnParam);
	checkf(CellSpawned, TEXT("***> No CellSpawned (nullptr) <***"));

	return CellSpawned;
}


void UCPP_AC_Cell_Division::ConfigureNewCell(ACPP_Cell* NewCell, FVector2f AxialLocation)
{
	const FString StrName = UCPP_CellFunctionLibrary::GetCellOutlinerLabel(AxialLocation);
	NewCell->SetActorLabel(StrName);
	NewCell->SetAxialLocation(AxialLocation);
	NewCell->LoadCellTypeComponents(OwnerCell->CellType);
}