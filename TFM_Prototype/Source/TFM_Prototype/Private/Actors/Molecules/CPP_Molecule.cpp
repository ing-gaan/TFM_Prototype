#include "Actors/Molecules/CPP_Molecule.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Actors/Molecules/CPP_DA_MoleculeType.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"
#include "Utils/Macros/Macros.h"



ACPP_Molecule::ACPP_Molecule()
{
	PrimaryActorTick.bCanEverTick = true;
}



void ACPP_Molecule::BeginPlay()
{
	Super::BeginPlay();

	InitEventBuses();
	InitMolecule();
	RegisterEventFunctions();
	SetActorScale3D(MoleculeType->MeshScale);
}


void ACPP_Molecule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACPP_Molecule::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterEventFunctions();
}



void ACPP_Molecule::RegisterEventFunctions()
{
	OnBeginCursorOver.AddUniqueDynamic(this, &ACPP_Molecule::BeginCursorOver);
	OnEndCursorOver.AddUniqueDynamic(this, &ACPP_Molecule::EndCursorOver);
	//OwnerCell->OnClicked.AddUniqueDynamic(this, &UCPP_AC_Cell_CursorInteraction::Clicked);
}


void ACPP_Molecule::UnRegisterEventFunctions()
{
	OnBeginCursorOver.RemoveDynamic(this, &ACPP_Molecule::BeginCursorOver);
	OnEndCursorOver.RemoveDynamic(this, &ACPP_Molecule::EndCursorOver);
	//OwnerCell->OnClicked.RemoveDynamic(this, &UCPP_AC_Cell_CursorInteraction::Clicked);
}



void ACPP_Molecule::BeginCursorOver(AActor* TouchedActor)
{
	InputEventBus->RaiseBeginCursorOverEvent(this);
}


void ACPP_Molecule::EndCursorOver(AActor* TouchedActor)
{
	InputEventBus->RaiseEndCursorOverEvent();
}



void ACPP_Molecule::InitEventBuses()
{
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;

	InputEventBus = GameInstance->GetSubsystem<UCPP_SS_InputEventBus>();
	checkf(InputEventBus, TEXT("***> No InputEventBus (nullptr) <***"));
}



void ACPP_Molecule::InitMolecule()
{
	float ZLocation = GameSettings->CellsDefaultHeightFromGround;
	FVector MoleculeLocation = GetActorLocation();
	MoleculeLocation.Z = ZLocation;
	SetActorLocation(MoleculeLocation);
	SetStaticMesh();
}



void ACPP_Molecule::SetStaticMesh()
{
	MoleculeStaticMeshComponent = GetComponentByClass<UStaticMeshComponent>();

	if (!MoleculeStaticMeshComponent)
	{
		UActorComponent* Component = AddComponentByClass(UStaticMeshComponent::StaticClass(), false, GetTransform(), false);
		MoleculeStaticMeshComponent = Cast<UStaticMeshComponent>(Component);
		checkf(MoleculeStaticMeshComponent, TEXT("*****> No CellStaticMeshComponent (nullptr) <*****"));
	}

	MoleculeStaticMeshComponent->SetStaticMesh(MoleculeType->MoleculeStaticMesh);
	MoleculeStaticMeshComponent->SetMaterial(0, MoleculeType->MoleculeMaterial);
}







