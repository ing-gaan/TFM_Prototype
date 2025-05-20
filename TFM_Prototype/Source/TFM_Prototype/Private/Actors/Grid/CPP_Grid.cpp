#include "Actors/Grid/CPP_Grid.h"
#include "Actors/Grid/Components/CPP_AC_Grid_StaticMeshInstances.h"



ACPP_Grid::ACPP_Grid()
{

	PrimaryActorTick.bCanEverTick = true;

}


void ACPP_Grid::BeginPlay()
{
	Super::BeginPlay();

	GetStaticMeshInstancesComponent();
	
}


void ACPP_Grid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACPP_Grid::GetStaticMeshInstancesComponent()
{
	StaticMeshInstancesComponent = GetComponentByClass<UCPP_AC_Grid_StaticMeshInstances>();

	if (!StaticMeshInstancesComponent)
	{
		checkf(StaticMeshInstancesComponent, TEXT("***> No StaticMeshInstancesComponent. (nullptr) <***"));
	}
}