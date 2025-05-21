#include "Actors/Grid/Components/CPP_AC_Grid_StaticMeshInstances.h"
#include "Actors/Grid/CPP_Grid.h"
#include <Kismet/GameplayStatics.h>
#include "Utils/FunctionLibraries/CPP_CellFunctionLibrary.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Utils/Macros/Macros.h"
#include "Core/GameControllers/CPP_PlayerController.h"





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

	SetNumCustomDataFloats(GridSettings->DefaultDataValues.Num());
	AddNewInstances(GridSettings->InitGridElementsNum);	
	SetValuesToAllInstances(GridSettings->DefaultDataValues);
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
	float Z = GameSettings->HiddenHeightFromGround;

	for (int i = 0; i < InstancesNum; i++)
	{
		InstancesTransforms.Add(FTransform(FVector(X, Y, Z)));
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
	ETraceTypeQuery TraceChannel = UEngineTypes::ConvertToTraceType(ECC_Visibility);
	bool bTraceComplex = true;
	FHitResult HitResult;

	PlayerController->GetHitResultUnderCursorByChannel(TraceChannel, bTraceComplex, HitResult);
	IndexHitByCursor = HitResult.Item;
	SetValuesToOneInstance(IndexHitByCursor, GridSettings->CursorOverDataValues);
	//PRINT("Begin cursor over %d", IndexHitByCursor);	
}



void UCPP_AC_Grid_StaticMeshInstances::EndCursorOver(UPrimitiveComponent* TouchedComponent)
{
	SetValuesToOneInstance(IndexHitByCursor, GridSettings->DefaultDataValues);
	//PRINT("End cursor over %d", IndexHitByCursor);
}


void UCPP_AC_Grid_StaticMeshInstances::Clicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{	
	GridOwner->ClickOnStaticMeshInstance(AxialLocationsOfVisibleInstances[IndexHitByCursor]);
}



void UCPP_AC_Grid_StaticMeshInstances::SetValuesToAllInstances(TArray<double> Values)
{
	for (int32 Index : InstacesIndexes)
	{
		SetValuesToOneInstance(Index, Values);
	}
}


void UCPP_AC_Grid_StaticMeshInstances::SetValuesToOneInstance(int32 Index, TArray<double> Values)
{	
	for (int i=0; i< Values.Num(); i++)
	{
		SetCustomDataValue(Index, i, Values[i], true);
	}	
}


void UCPP_AC_Grid_StaticMeshInstances::SetInstancesTransforms(const TSet<FVector2f> AxialLocations)
{	
	AxialLocationsOfVisibleInstances.Empty();
	AxialLocationsOfVisibleInstances = AxialLocations.Array();

	TArray<FTransform> TransformsOfVisibleInstances;
	FTransform NewTransform = GridOwner->GetActorTransform();
	float Distance = GridSettings->DistanceBetweenNeighbours;
	FVector2f OriginAxLoc = FVector2f::Zero();
	FVector2D RelativeLoc;
	float Z = 0;	
		
	for (const FVector2f& AxialLocation : AxialLocations)
	{		
		UCPP_CellFunctionLibrary::GetRelativeLocationFromAnOrigin(Distance, OriginAxLoc, AxialLocation, RelativeLoc);		
		NewTransform.SetLocation(FVector(RelativeLoc.X, RelativeLoc.Y, Z) );
		TransformsOfVisibleInstances.Add(NewTransform);
	}

	BatchUpdateInstancesTransforms(0, TransformsOfVisibleInstances, false, true);
}