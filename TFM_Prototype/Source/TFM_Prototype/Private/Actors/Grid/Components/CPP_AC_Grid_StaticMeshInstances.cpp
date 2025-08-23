#include "Actors/Grid/Components/CPP_AC_Grid_StaticMeshInstances.h"
#include "Actors/Grid/CPP_Grid.h"
#include <Kismet/GameplayStatics.h>
#include "Utils/FunctionLibraries/CPP_FuncLib_CellUtils.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Utils/Macros/Macros.h"
#include "Core/GameControllers/CPP_PlayerController.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Core/Subsystems/Managers/CPP_SS_LocalGameManager.h"
#include "Actors/Cell/CPP_Cell.h"




void UCPP_AC_Grid_StaticMeshInstances::BeginPlay()
{
	Super::BeginPlay();
	RegisterEventFunctions();
}


void UCPP_AC_Grid_StaticMeshInstances::InitComponent()
{
	PlayerController = Cast<ACPP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	checkf(PlayerController, TEXT("***> No PlayerController. Cast fail (nullptr) <***"));

	GridOwner = Cast<ACPP_Grid>(GetOwner());
	checkf(GridOwner, TEXT("*****> No OwnerCell (nullptr) <*****"));

	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;
	GridSettings = GameSettings->GridSettings;

	InstacesIndexes.Empty();
	InstancesInteractivity.Empty();

	SetNumCustomDataFloats(GridSettings->MaterialDataValuesNumber);
	AddNewInstances(GridSettings->InitGridElementsNum);	
	SetValuesToAllInstances(GridSettings->DefaultColor);

}


void UCPP_AC_Grid_StaticMeshInstances::AddExtraInstances()
{
	AddNewInstances(GridSettings->NewExtraGridElementsNum);
}


void UCPP_AC_Grid_StaticMeshInstances::AddNewInstances(int InstancesNum)
{
	TArray<FTransform> InstancesTransforms;
	float X = 0;
	float Y = 0;
	float Z = GridSettings->GridHiddenHeightFromGround;

	for (int i = 0; i < InstancesNum; i++)
	{
		InstancesTransforms.Emplace(FTransform(FVector(X, Y, Z)));
		InstancesInteractivity.Emplace(false);
	}
	InstacesIndexes = AddInstances(InstancesTransforms, true, false, true);
}



void UCPP_AC_Grid_StaticMeshInstances::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UnRegisterEventFunctions();
}


void UCPP_AC_Grid_StaticMeshInstances::RegisterEventFunctions()
{
	OnBeginCursorOver.AddUniqueDynamic(this, &UCPP_AC_Grid_StaticMeshInstances::BeginCursorOver);
	OnEndCursorOver.AddUniqueDynamic(this, &UCPP_AC_Grid_StaticMeshInstances::EndCursorOver);
	OnClicked.AddUniqueDynamic(this, &UCPP_AC_Grid_StaticMeshInstances::Clicked);
}


void UCPP_AC_Grid_StaticMeshInstances::UnRegisterEventFunctions()
{
	OnBeginCursorOver.RemoveDynamic(this, &UCPP_AC_Grid_StaticMeshInstances::BeginCursorOver);
	OnEndCursorOver.RemoveDynamic(this, &UCPP_AC_Grid_StaticMeshInstances::EndCursorOver);
	OnClicked.RemoveDynamic(this, &UCPP_AC_Grid_StaticMeshInstances::Clicked);
}



void UCPP_AC_Grid_StaticMeshInstances::BeginCursorOver(UPrimitiveComponent* TouchedComponent)
{	
	bool bAreCellsShifting = UCPP_SS_LocalGameManager::AreCellsShifting();
	if (bAreCellsShifting)
	{
		return;
	}

	ETraceTypeQuery TraceChannel = UEngineTypes::ConvertToTraceType(ECC_Visibility);
	bool bTraceComplex = true;
	FHitResult HitResult;

	PlayerController->GetHitResultUnderCursorByChannel(TraceChannel, bTraceComplex, HitResult);
	IndexHitByCursor = HitResult.Item;
	
	bool bIsInstanceInteractive = InstancesInteractivity[IndexHitByCursor];
	if (bIsInstanceInteractive)
	{
		SetValuesToOneInstance(IndexHitByCursor, GridSettings->CursorOverColor);
	}
	
}



void UCPP_AC_Grid_StaticMeshInstances::EndCursorOver(UPrimitiveComponent* TouchedComponent)
{
	bool bIsInstanceInteractive = InstancesInteractivity[IndexHitByCursor];
	if (bIsInstanceInteractive)
	{
		SetValuesToOneInstance(IndexHitByCursor, GridSettings->DefaultColor);
	}	
}


void UCPP_AC_Grid_StaticMeshInstances::Clicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{	
	bool bAreCellsShifting = UCPP_SS_LocalGameManager::AreCellsShifting();
	if (bAreCellsShifting)
	{
		return;
	}

	bool bIsInstanceInteractive = InstancesInteractivity[IndexHitByCursor];
	if (bIsInstanceInteractive)
	{
		GridOwner->ClickOnStaticMeshInstance(AxialLocationsOfVisibleInstances[IndexHitByCursor]);
	}

}



void UCPP_AC_Grid_StaticMeshInstances::SetValuesToAllInstances(FLinearColor StateColor)
{
	for (int32 Index : InstacesIndexes)
	{
		SetValuesToOneInstance(Index, StateColor);
	}
}


void UCPP_AC_Grid_StaticMeshInstances::SetValuesToOneInstance(int32 Index, FLinearColor StateColor)
{		
	SetCustomDataValue(Index, 0, StateColor.R, true);
	SetCustomDataValue(Index, 1, StateColor.G, true);
	SetCustomDataValue(Index, 2, StateColor.B, true);
	SetCustomDataValue(Index, 3, StateColor.A, true);

}


void UCPP_AC_Grid_StaticMeshInstances::SetInstancesTransforms(const TSet<FVector2f> AxialLocations)
{	
	if (AxialLocations.Num() > InstacesIndexes.Num())
	{
		AddExtraInstances();
	}
	
	AxialLocationsOfVisibleInstances.Empty();
	AxialLocationsOfVisibleInstances = AxialLocations.Array();

	TArray<FTransform> TransformsOfVisibleInstances;
	FTransform NewTransform = GridOwner->GetActorTransform();
	float Distance = GridSettings->DistanceBetweenNeighbours;
	FVector2f OriginAxLoc = FVector2f::Zero();
	FVector2D RelativeLoc;
	float Z = 0;

	int i = 0;
		
	for (const FVector2f& AxialLocation : AxialLocations)
	{		
		UCPP_FuncLib_CellUtils::GetRelativeLocationFromAnOrigin(Distance, OriginAxLoc, AxialLocation, RelativeLoc);		
		NewTransform.SetLocation(FVector(RelativeLoc.X, RelativeLoc.Y, Z) );
		TransformsOfVisibleInstances.Emplace(NewTransform);
		
		SetInstancesInteractivity(AxialLocation, i);
		i++;
	}

	BatchUpdateInstancesTransforms(0, TransformsOfVisibleInstances, false, true);
}



void UCPP_AC_Grid_StaticMeshInstances::SetInstancesInteractivity(FVector2f AxialLocation, int Index)
{
	const ACPP_Cell* Clicked = UCPP_SS_LocalGameManager::GetCurrentClickedCell();
	if (!Clicked)
	{
		return;
	}

	FVector2f ClickedAxLoc = Clicked->GetAxialLocation();
	bool bIsCloseToCLicked = UCPP_FuncLib_CellUtils::AreNeighbours(AxialLocation, ClickedAxLoc);
	InstancesInteractivity[Index] = bIsCloseToCLicked;
	
	if (bIsCloseToCLicked)
	{
		SetValuesToOneInstance(Index, GridSettings->DefaultColor);
		return;
	}

	SetValuesToOneInstance(Index, GridSettings->NotInteractiveColor);
}