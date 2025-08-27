#include "Actors/Cell/Components/CPP_AC_Cell_EnergyAccumulation.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Core/Subsystems/EventBuses/CPP_SS_TimeEventBus.h"
#include "Utils/FunctionLibraries/CPP_FuncLib_CellUtils.h"
#include "Core/Subsystems/Managers/CPP_SS_LocalGameManager.h"
#include "Utils/Macros/Macros.h"




void UCPP_AC_Cell_EnergyAccumulation::BeginPlay()
{
	Super::BeginPlay();
	InitComponent();
	RegisterEventFunctions();
}


void UCPP_AC_Cell_EnergyAccumulation::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterEventFunctions();
}


void UCPP_AC_Cell_EnergyAccumulation::InitComponent()
{
	Super::InitComponent();

	TransferEnergyTimeInterval = OwnerCell->CellType->TransferEnergyTimeInterval * 100;
}



void UCPP_AC_Cell_EnergyAccumulation::RegisterEventFunctions()
{
	TimeEventBus->TenMilliSecondsEventDelegate.AddUniqueDynamic(
		this, &UCPP_AC_Cell_EnergyAccumulation::TenMilliSecondsEvent);
}


void UCPP_AC_Cell_EnergyAccumulation::UnRegisterEventFunctions()
{
	TimeEventBus->TenMilliSecondsEventDelegate.RemoveDynamic(
		this, &UCPP_AC_Cell_EnergyAccumulation::TenMilliSecondsEvent);
}



void UCPP_AC_Cell_EnergyAccumulation::TenMilliSecondsEvent(int TensMilliSecondsCount)
{
	if (!OwnerCell->CellType->bCanTransferEnergyByItSelf)
	{
		return;
	}

	if (TensMilliSecondsCount % TransferEnergyTimeInterval == 0)
	{
		GetThoseWhoReceiveTheEnergy();
	}
}



void UCPP_AC_Cell_EnergyAccumulation::GetThoseWhoReceiveTheEnergy()
{
	float EnergyToTransfer = OwnerCell->GetCellEnergy() - OwnerCell->CellType->SubsistenceEnergy;
	if (EnergyToTransfer <= 0)
	{
		return;
	}

	int Range = OwnerCell->CellType->TransferRange;
	TArray<ACPP_Cell*> NeighboursInRange;
	OwnerCell->GetCellsNeighborsInRange(Range, NeighboursInRange);

	if (NeighboursInRange.Num() == 0)
	{
		return;
	}
		

	float EnergyPerCell = EnergyToTransfer / NeighboursInRange.Num();

	NeighboursInRange.HeapSort([](const ACPP_Cell& A, const ACPP_Cell& B)->bool
		{
			return A.GetCellEnergy() > B.GetCellEnergy();
		});


	int RemainingNeighbours = NeighboursInRange.Num();

	for (ACPP_Cell* Cell: NeighboursInRange)
	{
		RemainingNeighbours--;
		float CellEnergy = Cell->GetCellEnergy();
		float MaxCellEnergy = Cell->CellType->MaxEnergy;	
		float EnergyToReachMax = MaxCellEnergy - CellEnergy;

		if (EnergyToReachMax >= EnergyPerCell)
		{			
			Cell->In_De_creaseCellEnergy(EnergyPerCell);
			EnergyToTransfer -= EnergyPerCell;
			OwnerCell->In_De_creaseCellEnergy(-EnergyPerCell);
		}
		else
		{
			Cell->In_De_creaseCellEnergy(EnergyToReachMax);
			EnergyToTransfer -= EnergyToReachMax;
			OwnerCell->In_De_creaseCellEnergy(-EnergyToReachMax);
			if(RemainingNeighbours > 0)
			{
				EnergyPerCell = EnergyToTransfer / RemainingNeighbours;
			}
			
		}			
	}
}