#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Utils/FunctionLibraries/CPP_CellFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>
#include "Core/GameControllers/CPP_PlayerController.h"
#include "Characters/Player/CPP_Player.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Utils/Macros/Macros.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Base.h"





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
	LoadComponents();	
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
};



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


void ACPP_Cell::LoadComponents()
{	
	CellStaticMeshComponent = GetComponentByClass<UStaticMeshComponent>();

	if (!CellStaticMeshComponent)
	{
		UActorComponent* Component = AddComponentByClass(UStaticMeshComponent::StaticClass(), false, GetTransform(), false);
		CellStaticMeshComponent = Cast<UStaticMeshComponent>(Component);
		checkf(CellStaticMeshComponent, TEXT("*****> No CellStaticMeshComponent (nullptr) <*****"));
	}

	CellStaticMeshComponent->SetStaticMesh(CellType->CellStaticMesh);

	TInlineComponentArray<UCPP_AC_Cell_Base*, 10> CurrentComponents;
	GetComponents(CurrentComponents);

	for (UCPP_AC_Cell_Base* Component : CurrentComponents)
	{
		
		if (!CellType->NecessaryCellComponents.Contains(Component->GetClass()))
		{
			//PRINT("COMPONENTE %s ELIMINADO", *Component->GetClass()->GetName());
			Component->DestroyComponent();
		}
	}

	for (TSubclassOf<UCPP_AC_Cell_Base> ComponentClass : CellType->NecessaryCellComponents)
	{
		if (!GetComponentByClass(ComponentClass))
		{
			UActorComponent* Component = AddComponentByClass(ComponentClass, false, GetTransform(), false);
			//PRINT("COMPONENTE %s AGREGADO", *Component->GetClass()->GetName());
		}
	}
}