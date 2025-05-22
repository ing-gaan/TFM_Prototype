#include "Actors/Cell/Components/CPP_AC_Cell_CursorInteraction.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Utils/Macros/Macros.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"



void UCPP_AC_Cell_CursorInteraction::BeginPlay()
{
	Super::BeginPlay();
	RegisterEventFunctions();
}

void UCPP_AC_Cell_CursorInteraction::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterEventFunctions();
}

void UCPP_AC_Cell_CursorInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



void UCPP_AC_Cell_CursorInteraction::RegisterEventFunctions() const
{
	OwnerCell->OnBeginCursorOver.AddUniqueDynamic(this, &UCPP_AC_Cell_CursorInteraction::BeginCursorOver);
	OwnerCell->OnEndCursorOver.AddUniqueDynamic(this, &UCPP_AC_Cell_CursorInteraction::EndCursorOver);
	OwnerCell->OnClicked.AddUniqueDynamic(this, &UCPP_AC_Cell_CursorInteraction::Clicked);

}


void UCPP_AC_Cell_CursorInteraction::UnRegisterEventFunctions() const
{
	OwnerCell->OnBeginCursorOver.RemoveDynamic(this, &UCPP_AC_Cell_CursorInteraction::BeginCursorOver);
	OwnerCell->OnEndCursorOver.RemoveDynamic(this, &UCPP_AC_Cell_CursorInteraction::EndCursorOver);
	OwnerCell->OnClicked.RemoveDynamic(this, &UCPP_AC_Cell_CursorInteraction::Clicked);
}


void UCPP_AC_Cell_CursorInteraction::BeginCursorOver(AActor* TouchedActor)
{
	SetMaterialColorParameter(OwnerCell->CellType->CursorOverColor);
}


void UCPP_AC_Cell_CursorInteraction::EndCursorOver(AActor* TouchedActor)
{
	SetMaterialColorParameter(OwnerCell->CellType->NormalColor);
}


void UCPP_AC_Cell_CursorInteraction::Clicked(AActor* TouchedActor, FKey ButtonPressed)
{	
	SetMaterialColorParameter(OwnerCell->CellType->ClickedColor);

	InputEventBus->RaiseClickOnCellEvent(OwnerCell);
}



void UCPP_AC_Cell_CursorInteraction::InitComponent()
{
	Super::InitComponent();

	UMaterial* Material = OwnerCell->CellType->CellNormalMaterial;
	MaterialInstance = UMaterialInstanceDynamic::Create(Material, nullptr);
	checkf(MaterialInstance, TEXT("*****> No MaterialInstance (nullptr) <*****"));

	OwnerCell->CellStaticMeshComponent->SetMaterial(0, MaterialInstance);		
	SetMaterialColorParameter(OwnerCell->CellType->NormalColor);
}


void UCPP_AC_Cell_CursorInteraction::SetMaterialColorParameter(const FLinearColor& MaterialColor)
{
	FName MaterialColorParameterName = OwnerCell->CellType->MaterialColorParameterName;
	MaterialInstance->SetVectorParameterValue(MaterialColorParameterName, MaterialColor);	
}