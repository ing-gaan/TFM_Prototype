#include "Actors/Grid/CPP_AuxiliaryGridElement.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Core/Subsystems/EventBuses/CPP_SS_CellsManagerEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_GameEventBus.h"
#include "Characters/Player/CPP_Player.h"
#include <Kismet/GameplayStatics.h>
#include "Utils/FunctionLibraries/CPP_FuncLib_CellUtils.h"
#include "Core/Subsystems/Managers/CPP_SS_LocalGameManager.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Grid/CPP_Grid.h"
#include "Utils/Enums/CPP_CellShiftState.h"
#include "Utils/Macros/Macros.h"





ACPP_AuxiliaryGridElement::ACPP_AuxiliaryGridElement()
{
	PrimaryActorTick.bCanEverTick = true;
	ShiftState = ECPP_CellShiftState::AtOriginLocation;
}


void ACPP_AuxiliaryGridElement::BeginPlay()
{
	Super::BeginPlay();
	
	InitEventBuses();
	InitElement();
	RegisterEventFunctions();
}


void ACPP_AuxiliaryGridElement::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterEventFunctions();
}


void ACPP_AuxiliaryGridElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACPP_AuxiliaryGridElement::InitEventBuses()
{
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	CellsManagerEventBus = GameInstance->GetSubsystem<UCPP_SS_CellsManagerEventBus>();
	checkf(CellsManagerEventBus, TEXT("***> No UIEventBus (nullptr) <***"));

	GameEventBus = GameInstance->GetSubsystem<UCPP_SS_GameEventBus>();
	checkf(GameEventBus, TEXT("***> No UIEventBus (nullptr) <***"));
}


void ACPP_AuxiliaryGridElement::RegisterEventFunctions()
{	
	OnBeginCursorOver.AddUniqueDynamic(this, &ACPP_AuxiliaryGridElement::BeginCursorOver);
	OnEndCursorOver.AddUniqueDynamic(this, &ACPP_AuxiliaryGridElement::EndCursorOver);
	OnClicked.AddUniqueDynamic(this, &ACPP_AuxiliaryGridElement::Clicked);

	GameEventBus->Phase2StartedEventDelegate.AddUniqueDynamic(
		this, &ACPP_AuxiliaryGridElement::Phase2StartedEvent);

	CellsManagerEventBus->BeginCellsShiftingEventDelegate.AddUniqueDynamic(
		this, &ACPP_AuxiliaryGridElement::CellsShiftingEvent);
	CellsManagerEventBus->CellsShiftingReturnEventDelegate.AddUniqueDynamic(
		this, &ACPP_AuxiliaryGridElement::CellsShiftingReturnEvent);
	CellsManagerEventBus->MoveCellsEventDelegate.AddUniqueDynamic(
		this, &ACPP_AuxiliaryGridElement::MoveCellsEvent);

}


void ACPP_AuxiliaryGridElement::UnRegisterEventFunctions()
{
	OnBeginCursorOver.RemoveDynamic(this, &ACPP_AuxiliaryGridElement::BeginCursorOver);
	OnEndCursorOver.RemoveDynamic(this, &ACPP_AuxiliaryGridElement::EndCursorOver);
	OnClicked.RemoveDynamic(this, &ACPP_AuxiliaryGridElement::Clicked);

	GameEventBus->Phase2StartedEventDelegate.RemoveDynamic(
		this, &ACPP_AuxiliaryGridElement::Phase2StartedEvent);

	CellsManagerEventBus->BeginCellsShiftingEventDelegate.RemoveDynamic(
		this, &ACPP_AuxiliaryGridElement::CellsShiftingEvent);
	CellsManagerEventBus->CellsShiftingReturnEventDelegate.RemoveDynamic(
		this, &ACPP_AuxiliaryGridElement::CellsShiftingReturnEvent);
	CellsManagerEventBus->MoveCellsEventDelegate.RemoveDynamic(
		this, &ACPP_AuxiliaryGridElement::MoveCellsEvent);

}


void ACPP_AuxiliaryGridElement::Phase2StartedEvent(UCPP_SS_CellsManager* TheCellsManager, ACPP_Grid* TheGrid)
{
	Grid = TheGrid;
}


void ACPP_AuxiliaryGridElement::InitElement()
{
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;
	GridSettings = GameSettings->GridSettings;	

	Player = Cast<ACPP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	checkf(Player, TEXT("***> No PlayerPawn. Cast fail (nullptr) <***"));

	SetMaterial();
	//CurrentZLocation = GameSettings->HiddenHeightFromGround;
	//SetActorLocation(FVector(0, 0, CurrentZLocation));
	SetElementVisibility(false);
}


void ACPP_AuxiliaryGridElement::SetMaterial()
{
	AuxElemStaticMesh = GetComponentByClass<UStaticMeshComponent>();
	checkf(AuxElemStaticMesh, TEXT("*****> No StaticMesh (nullptr) <*****"));

	UMaterialInterface* Material = AuxElemStaticMesh->GetMaterial(0);
	MaterialInstance = UMaterialInstanceDynamic::Create(Material, nullptr);
	checkf(MaterialInstance, TEXT("*****> No MaterialInstance (nullptr) <*****"));

	AuxElemStaticMesh->SetMaterial(0, MaterialInstance);
	SetMaterialColorParameter(GridSettings->AuxElemNormalColor);
}



void ACPP_AuxiliaryGridElement::BeginCursorOver(AActor* TouchedActor)
{
	SetMaterialColorParameter(GridSettings->AuxElemCursorOverColor);
}


void ACPP_AuxiliaryGridElement::EndCursorOver(AActor* TouchedActor)
{
	SetMaterialColorParameter(GridSettings->AuxElemNormalColor);
}


void ACPP_AuxiliaryGridElement::Clicked(AActor* TouchedComponent, FKey ButtonPressed)
{
	SetMaterialColorParameter(GridSettings->AuxElemClickedColor);
	Grid->ClickOnAuxGridElement(AxialLocation);
	CellsShiftingReturnEvent();
}


void ACPP_AuxiliaryGridElement::SetMaterialColorParameter(const FLinearColor& MaterialColor)
{
	FName MaterialColorParameterName = GridSettings->AuxElemMaterialColorParamName;
	MaterialInstance->SetVectorParameterValue(MaterialColorParameterName, MaterialColor);
}



void ACPP_AuxiliaryGridElement::CellsShiftingEvent(const ACPP_Cell* FirstCellToShift)
{
	//const ACPP_Cell* ClickedCell = UCPP_SS_LocalGameManager::GetCurrentClickedCell();
	//AxialLocation = ClickedCell->GetAxialLocation();

	//CurrentZLocation = GameSettings->GridDefaultHeightFromGround;

	//SetElementVisibility(true);
	AxialLocation = FirstCellToShift->GetAxialLocation();

	// Listen by BP_Cell
	AnimShiftEventDelegate.Broadcast();
}


void ACPP_AuxiliaryGridElement::MoveCellsEvent(bool bCellsMoving)
{
	SetRelativeLocation(AxialLocation);
}


void ACPP_AuxiliaryGridElement::CellsShiftingReturnEvent()
{
	//SetLocation(GameSettings->GridDefaultHeightFromGround);

	// Listen by BP_Cell
	AnimReturnEventDelegate.Broadcast();
	//SetElementVisibility(false);
}



void ACPP_AuxiliaryGridElement::SetShiftState(ECPP_CellShiftState CurrentShiftState)
{
	ShiftState = CurrentShiftState;
	UCPP_SS_LocalGameManager::AuxGridElemShiftState = CurrentShiftState;
}


//void ACPP_AuxiliaryGridElement::CancelEvent()
//{
//	
//}


void ACPP_AuxiliaryGridElement::SetRelativeLocation(FVector2f AxLocation)
{
	FVector2f OriginAxLocation{ FVector2f(0, 0) };

	if (Player)
	{
		OriginAxLocation = Player->GetAxialLocation();
	}

	UCPP_FuncLib_CellUtils::GetRelativeLocationFromAnOrigin(GridSettings->DistanceBetweenNeighbours,
		OriginAxLocation, AxLocation, RelativeLocation);

	FVector RealLocation;
	FRotator RealRotation;

	UCPP_FuncLib_CellUtils::CalculateWorldLocationRotationBasedOnPlayer(
		Player, RelativeLocation, RealLocation, RealRotation);

	RealLocation.Z = CurrentZLocation;

	SetActorLocation(RealLocation);
	SetActorRotation(RealRotation);
}


void ACPP_AuxiliaryGridElement::SetElementVisibility(bool bIsVisible)
{
	CurrentZLocation = GridSettings->GridHiddenHeightFromGround;
	if (bIsVisible)
	{
		CurrentZLocation = GridSettings->GridDefaultHeightFromGround;
	}
	SetRelativeLocation(AxialLocation);
}



void ACPP_AuxiliaryGridElement::FinishCellsShifting()
{
	CellsManagerEventBus->RaiseFinishCellsShiftingEvent();
}





