#include "Characters/Bacteria/CPP_Bacteria.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Characters/Bacteria/CPP_DA_BacteriaType.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_CellsManagerEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_TimeEventBus.h"
#include "Utils/Macros/Macros.h"
#include "Utils/FunctionLibraries/CPP_FuncLib_CellUtils.h"
#include "Actors/Cell/CPP_Cell.h"







ACPP_Bacteria::ACPP_Bacteria()
{
	PrimaryActorTick.bCanEverTick = true;
}



void ACPP_Bacteria::BeginPlay()
{
	Super::BeginPlay();

	//SetActorScale3D(BacteriaType->MeshScale);

	InitEventBuses();
	InitMolecule();
	RegisterEventFunctions();
}


void ACPP_Bacteria::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACPP_Bacteria::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterEventFunctions();
}



void ACPP_Bacteria::RegisterEventFunctions()
{
	OnBeginCursorOver.AddUniqueDynamic(this, &ACPP_Bacteria::BeginCursorOver);
	OnEndCursorOver.AddUniqueDynamic(this, &ACPP_Bacteria::EndCursorOver);
	
	CellsManagerEventBus->MoveCellsEventDelegate.AddUniqueDynamic(
		this, &ACPP_Bacteria::MoveCellsEvent);

	TimeEventBus->OneSecondEventDelegate.AddUniqueDynamic(
		this, &ACPP_Bacteria::OneSecondEvent);
}


void ACPP_Bacteria::UnRegisterEventFunctions()
{
	OnBeginCursorOver.RemoveDynamic(this, &ACPP_Bacteria::BeginCursorOver);
	OnEndCursorOver.RemoveDynamic(this, &ACPP_Bacteria::EndCursorOver);
	
	CellsManagerEventBus->MoveCellsEventDelegate.RemoveDynamic(
		this, &ACPP_Bacteria::MoveCellsEvent);

	TimeEventBus->OneSecondEventDelegate.RemoveDynamic(
		this, &ACPP_Bacteria::OneSecondEvent);
}



void ACPP_Bacteria::BeginCursorOver(AActor* TouchedActor)
{
	InputEventBus->RaiseBeginCursorOverEvent(this);
}


void ACPP_Bacteria::EndCursorOver(AActor* TouchedActor)
{
	InputEventBus->RaiseEndCursorOverEvent();
}



void ACPP_Bacteria::InitEventBuses()
{
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;

	InputEventBus = GameInstance->GetSubsystem<UCPP_SS_InputEventBus>();
	checkf(InputEventBus, TEXT("***> No InputEventBus (nullptr) <***"));

	CellsManagerEventBus = GameInstance->GetSubsystem<UCPP_SS_CellsManagerEventBus>();
	checkf(CellsManagerEventBus, TEXT("***> No CellsManagerEventBus (nullptr) <***"));

	TimeEventBus = GameInstance->GetSubsystem<UCPP_SS_TimeEventBus>();
	checkf(TimeEventBus, TEXT("***> No UIEventBus (nullptr) <***"));

}



void ACPP_Bacteria::InitMolecule()
{
	float ZLocation = GameSettings->CellsDefaultHeightFromGround;
	FVector MoleculeLocation = GetActorLocation();
	MoleculeLocation.Z = ZLocation;
	SetActorLocation(MoleculeLocation);
	SetStaticMesh();
}



void ACPP_Bacteria::SetStaticMesh()
{
	MoleculeStaticMeshComponent = GetComponentByClass<UStaticMeshComponent>();

	if (!MoleculeStaticMeshComponent)
	{
		UActorComponent* Component = AddComponentByClass(UStaticMeshComponent::StaticClass(), false, GetTransform(), false);
		MoleculeStaticMeshComponent = Cast<UStaticMeshComponent>(Component);
		checkf(MoleculeStaticMeshComponent, TEXT("*****> No CellStaticMeshComponent (nullptr) <*****"));
	}

	MoleculeStaticMeshComponent->SetStaticMesh(BacteriaType->BacteriaStaticMesh);
	MoleculeStaticMeshComponent->SetMaterial(0, BacteriaType->BacteriaMaterial);
}



void ACPP_Bacteria::MoveCellsEvent(bool bCellsMoving)
{
	if (!bIsAttachedToGrid)
	{
		return;
	}

	FVector Location = PhantomCell->GetActorLocation();
	Location.Z = GameSettings->CellsDefaultHeightFromGround;
	
	SetActorLocation(Location);
	SetActorRotation(PhantomCell->GetActorRotation());
}


void ACPP_Bacteria::OneSecondEvent(int SecondsCount)
{	
	LifePoints -= 0.1f;
	if (LifePoints <= 0)
	{
		float MinPoints = BacteriaType->MaxLifePoints* BacteriaType->InitMinPercentLife / 100;
		float MaxPoints = BacteriaType->MaxLifePoints* BacteriaType->InitMaxPercentLife / 100;
		
		LifePoints = FMath::FRandRange(MinPoints, MaxPoints);
	}
}


bool ACPP_Bacteria::AddStolenLifePoints(float StolenPoints)
{
	LifePoints += StolenPoints;

	if (LifePoints >= BacteriaType->MaxLifePoints)
	{
		LifePoints = BacteriaType->MaxLifePoints;
		BPIE_NotifyFullPoints();
		return true;
	}
	return false;
}