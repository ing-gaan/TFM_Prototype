#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Utils/FunctionLibraries/CPP_FuncLib_CellUtils.h"
#include <Kismet/GameplayStatics.h>
#include "Core/GameControllers/CPP_PlayerController.h"
#include "Characters/Player/CPP_Player.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Utils/Macros/Macros.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Base.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Core/Subsystems/Managers/CPP_SS_CellsManager.h"
#include "Utils/Enums/CPPE_CellShiftState.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_Life_Base.h"
#include "Actors/Molecules/CPP_Molecule.h"
#include "Actors/Molecules/CPP_DA_MoleculeType.h"





UCPP_SS_CellsManager* ACPP_Cell::CellsManager{ nullptr };


ACPP_Cell::ACPP_Cell()
{
	PrimaryActorTick.bCanEverTick = true;
	CellShiftState = ECPPE_CellShiftState::AtOriginLocation;
}



void ACPP_Cell::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ACPP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	checkf(PlayerController, TEXT("***> No PlayerController. Cast fail (nullptr) <***"));

	Player = Cast<ACPP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	checkf(Player, TEXT("***> No PlayerPawn. Cast fail (nullptr) <***"));

	RegisterEventFunctions();
	InitCell();	

	CurrentMovementSpeed = CellType->MovementSpeedMultiplier;
	CurrentRotationSpeed = CellType->RotationSpeedMultiplier;
}



void ACPP_Cell::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);		
	UnRegisterEventFunctions();
}



void ACPP_Cell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ACPP_Cell::RegisterEventFunctions() const
{
	
}


void ACPP_Cell::UnRegisterEventFunctions() const
{

}



void ACPP_Cell::InitCell()
{		
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;
	GridSettings = GameSettings->GridSettings;

	bIsCellMoving = true;

}



FVector2f ACPP_Cell::GetAxialLocation() const
{
	return AxialLocation;
}



FVector2D ACPP_Cell::GetRelativeLocation() const
{
	return RelativeLocation;
}


ACPP_Cell* ACPP_Cell::Divide(FVector2f NewAxialLocation) const
{
	return DivideEventDelegate.Execute(NewAxialLocation);
}



void ACPP_Cell::BeginDifferentiate(const TSoftObjectPtr<UCPP_DA_CellType> Newtype) const
{
	BeginDifferentiateEventDelegate.Execute(Newtype);
}


void ACPP_Cell::FinishDifferentiate() const
{
	FinishDifferentiateEventDelegate.Broadcast();	
	Unclick();
}


void ACPP_Cell::SetAxialLocation(FVector2f NewAxialLocation)
{
	AxialLocation = NewAxialLocation;
	SetRelativeLocation(NewAxialLocation);
	SetCellLabel();
}


void ACPP_Cell::SetRelativeLocation(FVector2f AxLocation)
{
	FVector2f OriginAxLocation { FVector2f(0, 0) };
	
	if (Player)
	{
		OriginAxLocation = Player->GetAxialLocation();
	}

	UCPP_FuncLib_CellUtils::GetRelativeLocationFromAnOrigin(GridSettings->DistanceBetweenNeighbours,
		OriginAxLocation, AxLocation, RelativeLocation);

	MoveCell(false, true);
}


bool ACPP_Cell::LoadCellTypeComponents(const UCPP_DA_CellType* NewCellType)
{	
	CellStaticMeshComponent = GetComponentByClass<UStaticMeshComponent>();

	if (!CellStaticMeshComponent)
	{
		UActorComponent* Component = AddComponentByClass(UStaticMeshComponent::StaticClass(), false, GetTransform(), false);
		CellStaticMeshComponent = Cast<UStaticMeshComponent>(Component);
		checkf(CellStaticMeshComponent, TEXT("*****> No CellStaticMeshComponent (nullptr) <*****"));
	}

	CellStaticMeshComponent->SetStaticMesh(NewCellType->CellStaticMesh);


	TInlineComponentArray<UCPP_AC_Cell_Base*, 10> CurrentComponents;
	GetComponents(CurrentComponents);

	for (UCPP_AC_Cell_Base* Component : CurrentComponents)
	{		
		if (!NewCellType->NecessaryCellComponents.Contains(Component->GetClass()))
		{
			Component->DestroyComponent();
		}
	}

	for (TSubclassOf<UCPP_AC_Cell_Base> ComponentClass : NewCellType->NecessaryCellComponents)
	{
		if (!GetComponentByClass(ComponentClass))
		{
			UActorComponent* Component = AddComponentByClass(ComponentClass, false, GetTransform(), false);
		}
	}
	
	//****** Temporal solution ******///
	CurrentMovementSpeed = CellType->MovementSpeedMultiplier;
	CurrentRotationSpeed = CellType->RotationSpeedMultiplier;

	return true;
}



void ACPP_Cell::Clicked(bool Clicked)
{
	bIsClicked = Clicked;
}



void ACPP_Cell::Unclick() const
{
	UnclickEventDelegate.ExecuteIfBound();
}


void ACPP_Cell::MoveCell(bool bCellsMoving, bool bIsShifting) const
{	
	MoveCellEventDelegate.Broadcast(bCellsMoving, bIsShifting);	
}


bool ACPP_Cell::HasThisAbility(TSubclassOf<UCPP_AC_Cell_Base> Ability) const
{
	return CellType->NecessaryCellComponents.Contains(Ability);	
}



void ACPP_Cell::NotifyShiftingActivated() const
{
	CellsManager->StartShiftingCellsLocations(this);
}


void ACPP_Cell::NotifyShiftingCanceled() const
{
	CellsManager->ReturnCellsToOriginLocation();
}


void ACPP_Cell::ShiftAxialLocation(FVector2f NewTempAxialLocation) const
{	
	bool bIsOnTempLocation = CellShiftState == ECPPE_CellShiftState::AtTempLocation;

	if (bIsOnTempLocation)
	{
		return;
	}

	ShiftEventDelegate.ExecuteIfBound(true);

	// Listen by BP_Cell
	AnimShiftLocationEventDelegate.Broadcast(NewTempAxialLocation);
}


void ACPP_Cell::ReturnToOriginAxialLocation() const
{
	ShiftEventDelegate.ExecuteIfBound(false);

	// Listen by BP_Cell
	AnimReturnToOriginEventDelegate.Broadcast();	
}


ECPPE_CellShiftState ACPP_Cell::GetCellShiftState() const
{
	return CellShiftState;
}


bool ACPP_Cell::CellLifeStateIsEqualOrOlderThan(TSubclassOf<UCPP_SM_Cell_Life_Base> LifeStage) const
{
	if (!CellLifeState)
	{
		return false;
	}
	return CellLifeState->IsThisEqualOrOlderThan(LifeStage);
};


bool ACPP_Cell::IsClicked() const
{
	return bIsClicked;
}



FVector2f ACPP_Cell::GetTempAxialLocation() const
{
	return TempAxialLocation;
}



void ACPP_Cell::UpdateToTemporalLocation()
{
	AxialLocation = TempAxialLocation;
	CellShiftState = ECPPE_CellShiftState::AtOriginLocation;
	ShiftEventDelegate.ExecuteIfBound(false);
	SetCellLabel();
}



void ACPP_Cell::SetCellLabel()
{
	CellLabel = UCPP_FuncLib_CellUtils::GetCellOutlinerLabel(AxialLocation);
	SetActorLabel(CellLabel);
}



void ACPP_Cell::In_De_creaseCellEnergy(float EnergyVariation)
{
	/*if (EnergyVariation.has_value())
	{
		CellEnergy += EnergyVariation.value();
		return;
	}
	CellEnergy += CellType->EnergyDecreaseRate;*/

	CellEnergy += EnergyVariation;
	CellEnergy = FMath::RoundToFloat(CellEnergy * 100.0f) / 100.0f;
	BPIE_NotifyEnergy(CellEnergy);
}



void ACPP_Cell::BeginCellApoptosis() const
{
	BeginCellApoptosisEventDelegate.Broadcast();
}



const UCPP_SM_Cell_Life_Base* ACPP_Cell::GetCellLifeState() const
{
	return CellLifeState;
}


void ACPP_Cell::SetCellLifeState(const UCPP_SM_Cell_Life_Base* Newstate)
{
	CellLifeState = Newstate;
	CellLifeStateName = Newstate->GetLifeStateName();
}


void ACPP_Cell::DestroyYourself()
{
	CellsManager->DestroyCell(this);
}


bool ACPP_Cell::IsConnectedToOldestCell()
{
	return bIsConnectedToOldestCell;
}


float ACPP_Cell::GetCellEnergy() const
{
	return CellEnergy;
}



void ACPP_Cell::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ACPP_Molecule* Molecule = Cast<ACPP_Molecule>(OtherActor);

	if (Molecule)
	{
		PRINT("Overlap Molecule");

		CellEnergy += Molecule->MoleculeType->EnergyItProvides;

		Molecule->Destroy();
	}	
}



FText ACPP_Cell::GetTooltipText_Implementation() const
{
	FText TooltipText = FText::FromString(TEXT("Cell Tooltip"));
	return TooltipText;
}



void ACPP_Cell::GetCellsNeighborsInRange(int RangeDistance, TArray<ACPP_Cell*>& OutNeighboursInRange) const
{
	CellsManager->GetNeighboursInRange(AxialLocation, RangeDistance, OutNeighboursInRange);
}