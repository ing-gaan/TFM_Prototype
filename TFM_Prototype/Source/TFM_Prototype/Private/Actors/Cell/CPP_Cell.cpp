#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Utils/FunctionLibraries/CPP_CellFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>
#include "Core/GameControllers/CPP_PlayerController.h"
#include "Characters/Player/CPP_Player.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Utils/Macros/Macros.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Base.h"
#include "Core/GameInstance/CPP_GameInstance.h"






ACPP_Cell::ACPP_Cell()
{
	PrimaryActorTick.bCanEverTick = true;
}



void ACPP_Cell::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ACPP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	checkf(PlayerController, TEXT("***> No PlayerController. Cast fail (nullptr) <***"));

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

	if (bIsCellMoving)
	{
		//MoveCell();
	}
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

}


//void ACPP_Cell::MoveCell()
//{
//	FVector RealLocation;
//	FRotator RealRotation;
//
//	UCPP_CellFunctionLibrary::CalculateWorldLocationRotationFromCenterCell(
//		PlayerController->GetFirstCell(), RelativeLocation, RealLocation, RealRotation);
//
//	SetActorLocation(RealLocation);
//	SetActorRotation(RealRotation);
//}


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
	SetRelativeLocation();
}



void ACPP_Cell::SetRelativeLocation()
{
	FVector2f OriginAxLocation { FVector2f(0, 0) };
	
	if (Player)
	{
		OriginAxLocation = Player->GetAxialLocation();
	}

	UCPP_CellFunctionLibrary::GetRelativeLocationFromAnOrigin(GridSettings->DistanceBetweenNeighbours,
		OriginAxLocation, AxialLocation, RelativeLocation);

	//MoveCellEventDelegate.Broadcast(true);
	//MoveCell();

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



void ACPP_Cell::Click() const
{
	ClickEventDelegate.Execute();
}

void ACPP_Cell::Unclick() const
{
	UnclickEventDelegate.Execute();
}




bool ACPP_Cell::HasThisAbility(TSubclassOf<UCPP_AC_Cell_Base> Ability) const
{
	return CellType->NecessaryCellComponents.Contains(Ability);
}



