#include "Actors/Grid/Components/CPP_AC_Grid_StaticMeshInstances.h"
#include <Kismet/GameplayStatics.h>
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Utils/Macros/Macros.h"
#include <Math/UnrealMathUtility.h>
#include "Core/GameControllers/CPP_PlayerController.h"





void UCPP_AC_Grid_StaticMeshInstances::BeginPlay()
{
	Super::BeginPlay();

	InitComponent();
	RegisterEventFunctions();
}


void UCPP_AC_Grid_StaticMeshInstances::InitComponent()
{
	PlayerController = Cast<ACPP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	checkf(PlayerController, TEXT("***> No PlayerController. Cast fail (nullptr) <***"));

	SetNumCustomDataFloats(GridSettings->DefaultDataValues.Num());

	for (int i = 0; i < GridSettings->InitGridElementsNum; i++)
	{
		float X = FMath::FRandRange(-1000.0, 1000.0);
		float Y = FMath::FRandRange(-1000.0, 1000.0);

		InstancesTransforms.Add(FTransform(FVector(X, Y, 10)));
	}

	InstacesIndexes = AddInstances(InstancesTransforms, true, false, true);
	SetValuesToAllInstances(GridSettings->DefaultDataValues);

	
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
}


void UCPP_AC_Grid_StaticMeshInstances::UnRegisterEventFunctions()
{
	OnBeginCursorOver.RemoveDynamic(this, &UCPP_AC_Grid_StaticMeshInstances::BeginCursorOver);
	OnEndCursorOver.RemoveDynamic(this, &UCPP_AC_Grid_StaticMeshInstances::EndCursorOver);
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

