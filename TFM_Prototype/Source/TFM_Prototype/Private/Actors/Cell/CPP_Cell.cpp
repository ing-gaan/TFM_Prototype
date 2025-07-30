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
#include "Utils/Enums/CPP_CellShiftState.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_Life_Base.h"






const UCPP_SS_CellsManager* ACPP_Cell::CellsManager{ nullptr };


ACPP_Cell::ACPP_Cell()
{
	PrimaryActorTick.bCanEverTick = true;
	CellShiftState = ECPP_CellShiftState::AtOriginLocation;
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



bool ACPP_Cell::Differentiate(const UCPP_DA_CellType* Newtype) const
{
	return DifferentiateEventDelegate.Execute(Newtype);
}


void ACPP_Cell::SetAxialLocation(FVector2f NewAxialLocation)
{
	AxialLocation = NewAxialLocation;
	SetRelativeLocation(NewAxialLocation);
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

	MoveCell();
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


void ACPP_Cell::MoveCell() const
{	
	MoveCellEventDelegate.ExecuteIfBound();
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
	bool bIsOnTempLocation = CellShiftState == ECPP_CellShiftState::AtTempLocation;

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


ECPP_CellShiftState ACPP_Cell::GetCellShiftState() const
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
	CellShiftState = ECPP_CellShiftState::AtOriginLocation;
	ShiftEventDelegate.ExecuteIfBound(false);
}


