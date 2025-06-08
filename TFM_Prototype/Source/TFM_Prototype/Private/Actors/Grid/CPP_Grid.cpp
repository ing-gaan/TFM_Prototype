#include "Actors/Grid/CPP_Grid.h"
#include <Kismet/GameplayStatics.h>
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Actors/Grid/Components/CPP_AC_Grid_StaticMeshInstances.h"
#include "Characters/Player/CPP_Player.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_UIEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_CellsManagerEventBus.h"
#include "Utils/Macros/Macros.h"




ACPP_Grid::ACPP_Grid()
{
	PrimaryActorTick.bCanEverTick = true;	
}

 
void ACPP_Grid::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ACPP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	checkf(Player, TEXT("***> No Player. Cast fail (nullptr) <***"));

	SetGridLocation();
	InitEventBuses();
	RegisterEventFunctions();
	GetStaticMeshInstancesComponent();	
}


void ACPP_Grid::SetGridLocation()
{
	SetActorTransform(Player->GetActorTransform());
	SetGridVisibility(false);
}


void ACPP_Grid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACPP_Grid::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UnRegisterEventFunctions();
}


void ACPP_Grid::InitEventBuses()
{
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UGameInstance* GameInstance = World->GetGameInstance();
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	InputEventBus = GameInstance->GetSubsystem<UCPP_SS_InputEventBus>();
	checkf(InputEventBus, TEXT("***> No InputEventBus (nullptr) <***"));

	UIEventBus = GameInstance->GetSubsystem<UCPP_SS_UIEventBus>();
	checkf(UIEventBus, TEXT("***> No UIEventBus (nullptr) <***"));

	CellsManagerEventBus = GameInstance->GetSubsystem<UCPP_SS_CellsManagerEventBus>();
	checkf(CellsManagerEventBus, TEXT("***> No CellsManagerEventBus (nullptr) <***"));

}



void ACPP_Grid::RegisterEventFunctions()
{
	InputEventBus->ClickOnCellEventDelegate.AddUniqueDynamic(
		this, &ACPP_Grid::ClickOnCellEvent);

	UIEventBus->BeginCellDivisionEventDelegate.AddUniqueDynamic(
		this, &ACPP_Grid::BeginCellDivisionEvent);

	CellsManagerEventBus->FinishCellDivisionEventDelegate.AddUniqueDynamic(
		this, &ACPP_Grid::FinishCellDivisionEvent);
}


void ACPP_Grid::UnRegisterEventFunctions()
{
	InputEventBus->ClickOnCellEventDelegate.RemoveDynamic(
		this, &ACPP_Grid::ClickOnCellEvent);

	UIEventBus->BeginCellDivisionEventDelegate.RemoveDynamic(
		this, &ACPP_Grid::BeginCellDivisionEvent);

	CellsManagerEventBus->FinishCellDivisionEventDelegate.RemoveDynamic(
		this, &ACPP_Grid::FinishCellDivisionEvent);
}


void ACPP_Grid::GetStaticMeshInstancesComponent()
{
	StaticMeshInstancesComponent = GetComponentByClass<UCPP_AC_Grid_StaticMeshInstances>();

	if (!StaticMeshInstancesComponent)
	{
		checkf(StaticMeshInstancesComponent, TEXT("***> No StaticMeshInstancesComponent. (nullptr) <***"));
	}
	StaticMeshInstancesComponent->InitComponent();
}


void ACPP_Grid::ClickOnCellEvent(const ACPP_Cell* NewClickedCell)
{
	checkf(NewClickedCell, TEXT("***> No NewClickedCell (nullptr) <***"));

	
}


void ACPP_Grid::BeginCellDivisionEvent()
{
	StaticMeshInstancesComponent->SetInstancesTransforms(FreeNeighbours);
	SetGridVisibility(true);
}


void ACPP_Grid::FinishCellDivisionEvent(FVector2f SpawnAxialLocation)
{
	//PRINT("Cell spawned");
	FreeNeighbours.Remove(SpawnAxialLocation);
	UsedAxialLocations.Emplace(SpawnAxialLocation);
	AddNewFreeNeighbours(SpawnAxialLocation);

	SetGridVisibility(false);
}


void ACPP_Grid::AddNewFreeNeighbours(FVector2f SpawnAxialLocation)
{
	FVector2f NeighbourAxialLoc;
	for (const FVector2f& Elem : GridSettings->InitAxialLocations)
	{
		NeighbourAxialLoc = Elem + SpawnAxialLocation;
		if (!UsedAxialLocations.Contains(NeighbourAxialLoc))
		{
			FreeNeighbours.Add(NeighbourAxialLoc);
		}
	}	
	//StaticMeshInstancesComponent->SetInstancesTransforms(FreeNeighbours);
	//SetGridVisibility(true);
}


void ACPP_Grid::SetGridVisibility(bool bIsVisible)
{
	float Z = GameSettings->HiddenHeightFromGround;
	if (bIsVisible)
	{
		Z = GameSettings->DefaultHeightFromGround;
	}
	
	float X = Player->GetActorLocation().X;
	float Y = Player->GetActorLocation().Y;
	SetActorLocation(FVector(X, Y, Z));
}


void ACPP_Grid::ClickOnStaticMeshInstance(FVector2f AxialLocation) const
{
	InputEventBus->RaiseClickOnGridEvent(AxialLocation);
	PRINT("Axial location clicked = (%f, %f)", AxialLocation.X, AxialLocation.Y);

}