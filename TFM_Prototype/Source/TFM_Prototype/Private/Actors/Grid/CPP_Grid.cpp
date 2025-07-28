#include "Actors/Grid/CPP_Grid.h"
#include <Kismet/GameplayStatics.h>
#include "Core/GameInstance/CPP_GameInstance.h"
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
	AddUsedAxialLocation(GameSettings->GridSettings->FirstAxialLocation);
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

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;
	GridSettings = GameSettings->GridSettings;

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
	InputEventBus->CancelEventDelegate.AddUniqueDynamic(
		this, &ACPP_Grid::CancelEvent);

	UIEventBus->BeginCellDivisionEventDelegate.AddUniqueDynamic(
		this, &ACPP_Grid::BeginCellDivisionEvent);

	CellsManagerEventBus->FinishCellDivisionEventDelegate.AddUniqueDynamic(
		this, &ACPP_Grid::FinishCellDivisionEvent);
}


void ACPP_Grid::UnRegisterEventFunctions()
{
	InputEventBus->ClickOnCellEventDelegate.RemoveDynamic(
		this, &ACPP_Grid::ClickOnCellEvent);
	InputEventBus->CancelEventDelegate.RemoveDynamic(
		this, &ACPP_Grid::CancelEvent);

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


void ACPP_Grid::ClickOnCellEvent(const ACPP_Cell* ClickedCell)
{
	CurrentClickedCell = ClickedCell;
	StaticMeshInstancesComponent->SetInstancesTransforms(FreeNeighbours);
}


void ACPP_Grid::CancelEvent()
{
	SetGridVisibility(false);
}


void ACPP_Grid::BeginCellDivisionEvent()
{
	SetGridVisibility(true);
}


void ACPP_Grid::FinishCellDivisionEvent(FVector2f SpawnAxialLocation)
{
	//AddUsedAxialLocation(SpawnAxialLocation);
}


void ACPP_Grid::AddNewFreeNeighbours(FVector2f SpawnAxialLocation)
{
	FVector2f NeighbourAxialLoc;
	for (const FVector2f& Elem : GridSettings->InitAxialLocations)
	{
		NeighbourAxialLoc = Elem + SpawnAxialLocation;
		if (!UsedAxialLocations.Contains(NeighbourAxialLoc))
		{
			FreeNeighbours.Emplace(NeighbourAxialLoc);
		}
	}	
}



void ACPP_Grid::RemoveFreeNeighbours(FVector2f AxialLocation)
{
	FVector2f TempAxLoc;
	
	for (const FVector2f& Elem : GridSettings->InitAxialLocations)
	{
		TempAxLoc = AxialLocation + Elem;
		FreeNeighbours.Remove(TempAxLoc);
	}

	for (const FVector2f& Elem : GridSettings->InitAxialLocations)
	{
		TempAxLoc = AxialLocation + Elem;
		if (UsedAxialLocations.Contains(TempAxLoc))
		{
			AddNewFreeNeighbours(TempAxLoc);
		}
	}
}


void ACPP_Grid::SetGridVisibility(bool bIsVisible)
{
	float Z = GameSettings->HiddenHeightFromGround;
	if (bIsVisible)
	{
		Z = GameSettings->GridDefaultHeightFromGround;
	}
	
	float X = Player->GetActorLocation().X;
	float Y = Player->GetActorLocation().Y;
	SetActorLocation(FVector(X, Y, Z));
}


void ACPP_Grid::ClickOnStaticMeshInstance(FVector2f AxialLocation)
{	
	FTimerDelegate TimerDelegate;
	FTimerHandle TimerHandle;
	TimerDelegate.BindUObject(this, &ACPP_Grid::ClickOnGrid, AxialLocation);
	GetWorldTimerManager().SetTimerForNextTick(TimerDelegate);	
}


void ACPP_Grid::ClickOnGrid(FVector2f AxialLocation)
{		
	AddUsedAxialLocation(AxialLocation);
	InputEventBus->RaiseClickOnGridEvent(AxialLocation);	
}


void ACPP_Grid::ClickOnAuxGridElement(FVector2f AxialLocation)
{	
	InputEventBus->RaiseClickOnAuxGridElemEvent();
	AddUsedAxialLocation(AxialLocation);
}


const TSet<FVector2f>* ACPP_Grid::GetAllFreeNeighbours() const
{
	return &FreeNeighbours;
}


void ACPP_Grid::UpdateToTempLocations(FVector2f FirstAxialLocation, FVector2f LastAxialLocation)
{	
	AddFreeAxialLocation(FirstAxialLocation);
	AddUsedAxialLocation(LastAxialLocation);	
}




void ACPP_Grid::AddFreeAxialLocation(FVector2f FreeAxialLocation)
{
	FreeNeighbours.Emplace(FreeAxialLocation);
	UsedAxialLocations.Remove(FreeAxialLocation);
	StaticMeshInstancesComponent->SetInstancesTransforms(FreeNeighbours);
}


void ACPP_Grid::AddUsedAxialLocation(FVector2f UsedAxialLocation)
{
	FreeNeighbours.Remove(UsedAxialLocation);
	UsedAxialLocations.Emplace(UsedAxialLocation);
	AddNewFreeNeighbours(UsedAxialLocation);
	StaticMeshInstancesComponent->SetInstancesTransforms(FreeNeighbours);
}
