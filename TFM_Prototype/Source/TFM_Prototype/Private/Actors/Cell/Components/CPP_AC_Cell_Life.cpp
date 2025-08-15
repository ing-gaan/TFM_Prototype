#include "Actors/Cell/Components/CPP_AC_Cell_Life.h"
#include "Actors/Cell/CPP_Cell.h"

#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/Subsystems/EventBuses/CPP_SS_TimeEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_GameEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_UIEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_Life_Context.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_Dying.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_Dead.h"
#include "Actors/Cell/StateMachines/EnergySM/CPP_SM_Cell_Energy_Context.h"
#include "Actors/Cell/CPP_DA_CellType.h"

#include "Utils/Macros/Macros.h"






UCPP_AC_Cell_Life::UCPP_AC_Cell_Life()
{
	//PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bCanEverTick = false;
}



void UCPP_AC_Cell_Life::BeginPlay()
{
	Super::BeginPlay();
	InitCellStateMachines();
	RegisterEventFunctions();
}


void UCPP_AC_Cell_Life::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterEventFunctions();
}


//void UCPP_AC_CellDeath::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//}


void UCPP_AC_Cell_Life::InitComponent() /// Component initialized on Super::BeginPlay()
{	
	Super::InitComponent(); 

	//int InitEnergy = OwnerCell->CellType->MaxEnergy * GameSettings->MaxCellsEnergyMultiplier;
	//OwnerCell->In_De_creaseCellEnergy(InitEnergy);

	float DecreaseRate = OwnerCell->CellType->EnergyDecreaseRate;
	float EnergyConsumptionMultiplier = GameSettings->StoppedEnergyConsumptionMultiplier;
	EnergyDecrease = DecreaseRate * EnergyConsumptionMultiplier;

	LifeStateTimeStep = GameSettings->LifeStateTimeStep * 100;
	EnergyTimeStep = GameSettings->EnergyTimeStep * 100;
}


void UCPP_AC_Cell_Life::InitCellStateMachines()
{
	UMaterial* Material = OwnerCell->CellType->CellNormalMaterial;
	MaterialInstance = UMaterialInstanceDynamic::Create(Material, nullptr);
	checkf(MaterialInstance, TEXT("*****> No MaterialInstance (nullptr) <*****"));

	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	LifeSMContext = NewObject<UCPP_SM_Cell_Life_Context>();
	checkf(LifeSMContext, TEXT("*****> No CellLifeStateMachineContext created (nullptr) <*****"));
	LifeSMContext->InitStateMachine(OwnerCell, MaterialInstance, World);
	ChangeCellLifeState(); /// Chage from CellLifeInitState to CellLifeBornState

	EnergySMContext = NewObject<UCPP_SM_Cell_Energy_Context>();
	checkf(EnergySMContext, TEXT("*****> No EnergyStateMachineContext created (nullptr) <*****"));
	EnergySMContext->InitStateMachine(OwnerCell, MaterialInstance, World);
	EnergySMContext->CheckEnergyState();
}



void UCPP_AC_Cell_Life::RegisterEventFunctions()
{
	OwnerCell->FinishDifferentiateEventDelegate.AddUniqueDynamic(
		this, &UCPP_AC_Cell_Life::FinishDifferentiateEvent);
	OwnerCell->BeginCellApoptosisEventDelegate.AddUniqueDynamic(
		this, &UCPP_AC_Cell_Life::BeginCellApoptosisEvent);
	OwnerCell->MoveCellEventDelegate.AddUniqueDynamic(
		this, &UCPP_AC_Cell_Life::MoveCellEvent);

	TimeEventBus->TenMilliSecondsEventDelegate.AddUniqueDynamic(
		this, &UCPP_AC_Cell_Life::TenMilliSecondsEvent);

	/*GameEventBus->FinishDestroyCellEventDelegate.AddUniqueDynamic(
		this, &UCPP_AC_Cell_Life::FinishDestroyCellEvent);*/
}


void UCPP_AC_Cell_Life::UnRegisterEventFunctions()
{
	OwnerCell->FinishDifferentiateEventDelegate.RemoveDynamic(
		this, &UCPP_AC_Cell_Life::FinishDifferentiateEvent);
	OwnerCell->BeginCellApoptosisEventDelegate.RemoveDynamic(
		this, &UCPP_AC_Cell_Life::BeginCellApoptosisEvent);
	OwnerCell->MoveCellEventDelegate.RemoveDynamic(
		this, &UCPP_AC_Cell_Life::MoveCellEvent);

	TimeEventBus->TenMilliSecondsEventDelegate.RemoveDynamic(
		this, &UCPP_AC_Cell_Life::TenMilliSecondsEvent);

	/*GameEventBus->FinishDestroyCellEventDelegate.RemoveDynamic(
		this, &UCPP_AC_Cell_Life::FinishDestroyCellEvent);*/
}



void UCPP_AC_Cell_Life::FinishDifferentiateEvent()
{
	//PRINT("CurrentStateTime= %f", LifeSMContext->CurrentState->GetCurrentStateTime());
	LifeSMContext->ChangeToNewCellTypeStates();
	//PRINT("New CurrentStateTime= %f", LifeSMContext->CurrentState->GetCurrentStateTime());
}


void UCPP_AC_Cell_Life::BeginCellApoptosisEvent()
{
	ChangeCellLifeState(UCPP_SM_Cell_LifeSt_Dying::StaticClass());
}


void UCPP_AC_Cell_Life::MoveCellEvent(bool bCellsMoving, bool bIsShifting)
{
	float DecreaseRate = OwnerCell->CellType->EnergyDecreaseRate;
	float EnergyConsumptionMultiplier = GameSettings->StoppedEnergyConsumptionMultiplier;

	if (bCellsMoving)
	{
		EnergyConsumptionMultiplier = GameSettings->MovingEnergyConsumptionMultiplier;
	}
	EnergyDecrease = DecreaseRate * EnergyConsumptionMultiplier;
}


void UCPP_AC_Cell_Life::TenMilliSecondsEvent()
{
	if (TensMilliSecondsPassed == INT_MAX)
	{
		/// When TensMilliSecondsPassed = INT_MAX = 2147483647 then
		/// 47 have passed since the last multiple of 100
		TensMilliSecondsPassed = 47;
	}
	TensMilliSecondsPassed++;

	if (TensMilliSecondsPassed % LifeStateTimeStep == 0)
	{
		OneLifeStateTimeStep();
	}

	if (TensMilliSecondsPassed % EnergyTimeStep == 0)
	{
		OneEnergyTimeStep();
	}
}


void UCPP_AC_Cell_Life::OneLifeStateTimeStep()
{
	DecreaseLifeStateTime();
}


void UCPP_AC_Cell_Life::OneEnergyTimeStep()
{
	DecreaseEnergy();
}





//void UCPP_AC_Cell_Life::FinishDestroyCellEvent()
//{
//	if (OwnerCell->IsConnectedToOldestCell())
//	{
//		return;
//	}
//	ChangeCellLifeState(UCPP_SM_Cell_LifeSt_Dying::StaticClass());
//}



void UCPP_AC_Cell_Life::DecreaseLifeStateTime()
{
	LifeSMContext->CurrentState->DecreaseStateTime();

	//PRINT("Cell state remaining time= %2.1f", LifeSMContext->CurrentState->GetRemainingStateTime());

	if (!LifeSMContext->CurrentState->StateTimeFinished())
	{
		return;
	}

	ChangeCellLifeState();
	if (LifeSMContext->CurrentState->IsA(UCPP_SM_Cell_LifeSt_Dead::StaticClass()))
	{
		DestroyCell();
	}
}



void UCPP_AC_Cell_Life::DecreaseEnergy()
{
	if (LifeSMContext->CurrentState->IsThisEqualOrOlderThan(UCPP_SM_Cell_LifeSt_Dying::StaticClass()))
	{
		return;
	}

	OwnerCell->In_De_creaseCellEnergy(-EnergyDecrease);
	PRINT("Cell Energy= %i", OwnerCell->GetCellEnergy());
	EnergySMContext->CheckEnergyState();

	if (OwnerCell->GetCellEnergy() <= 0)
	{
		ChangeCellLifeState(UCPP_SM_Cell_LifeSt_Dying::StaticClass());
		PRINT("%s DYING - NO ENERGY", *(OwnerCell->GetActorLabel()));
	}
}



void UCPP_AC_Cell_Life::ChangeCellLifeState(std::optional<TSubclassOf<UCPP_SM_Cell_Life_Base>> StateType)
{
	if (StateType.has_value())
	{
		LifeSMContext->ChangeState(StateType.value());
	}
	else
	{
		LifeSMContext->ChangeState();
	}
	OwnerCell->SetCellLifeState(LifeSMContext->CurrentState);

	//PRINT("%s in STATE= %s", *(OwnerCell->GetActorLabel()), *(OwnerCell->CellLifeState->GetName()));
}


void UCPP_AC_Cell_Life::DestroyCell()
{
	/*FVector2f OwnerCellAxiallocation = OwnerCell->AxialLocation;

	if (ACPP_Cell::CurrentClickedCell == OwnerCell)
	{
		InputEventBus->RaiseCancelEvent();
	}

	PRINT("%s IS DEAD", *(OwnerCell->GetActorLabel()));*/

	/*GameEventBus->RaiseBeginDestroyCellEvent(OwnerCell);

	SetDeadCellNeighbours();
	OwnerCell->Destroy();
	UpdateDeadCellNeighbours();

	GameEventBus->RaiseFinishDestroyCellEvent();*/

	OwnerCell->DestroyYourself();
	OwnerCell->Destroy();
}


//void UCPP_AC_Cell_Life::UpdateDeadCellNeighbours()
//{
//	for (ACPP_Cell* Neighbour : ACPP_Cell::OneCellNeighbours)
//	{
//		Neighbour->CheckConnectionToOldestCell();
//		ACPP_Cell::TempCellsReferences.Emplace(Neighbour);
//	}
//	int MaxNeighBourNum = GameSettings->InitAxialLocations.Num();
//
//	ACPP_Cell::OneCellNeighbours.Reset();
//	ACPP_Cell::TempCellsReferences.Reset(MaxNeighBourNum);
//}
//
//
//void UCPP_AC_Cell_Life::SetDeadCellNeighbours()
//{
//	OwnerCell->PlayerController->GetCellNeighbours(OwnerCell, ACPP_Cell::OneCellNeighbours);
//}
