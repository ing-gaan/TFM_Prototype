#include "Actors/Cell/Components/CPP_AC_Cell_Differentiation.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Engine/AssetManager.h"



void UCPP_AC_Cell_Differentiation::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterEventFunctions();
}


void UCPP_AC_Cell_Differentiation::InitComponent()
{
	Super::InitComponent();
	RegisterEventFunctions();
}


void UCPP_AC_Cell_Differentiation::RegisterEventFunctions() const
{
	OwnerCell->BeginDifferentiateEventDelegate.BindDynamic(this, &UCPP_AC_Cell_Differentiation::BeginDifferentiateEvent);
}


void UCPP_AC_Cell_Differentiation::UnRegisterEventFunctions() const
{
	OwnerCell->BeginDifferentiateEventDelegate.Clear();
	
}



void UCPP_AC_Cell_Differentiation::BeginDifferentiateEvent(TSoftObjectPtr<const UCPP_DA_CellType> NewType)
{
	FSoftObjectPath AssetPath = NewType.ToSoftObjectPath();
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	/*StreamableManager.RequestAsyncLoad(NewCellType.ToSoftObjectPath(),
		FStreamableDelegate::CreateUObject(this, &UCPP_AC_Cell_Differentiation::LoadCellTypeSoftRef));*/

	ACPP_Cell* Cell = OwnerCell;

	FStreamableDelegate Delegate = FStreamableDelegate::CreateLambda([=]()
		{
			if (!NewType.IsValid())
			{
				return;
			}
			Cell->CellType = NewType.Get();

			if (Cell->LoadCellTypeComponents(NewType.Get()))
			{
				Cell->FinishDifferentiate();
			}
		});

	StreamableManager.RequestAsyncLoad(AssetPath, Delegate);

	/*StreamableManager.LoadSynchronous(NewType);

	if (!NewType.IsValid())
	{
		return;
	}
	Cell->CellType = NewType.Get();

	if (Cell->LoadCellTypeComponents(NewType.Get()))
	{
		Cell->FinishDifferentiate();
	}*/

}







