#include "Actors/Cell/Components/CPP_AC_Cell_CursorInteraction.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Utils/Macros/Macros.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Context.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Init.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"








UCPP_AC_Cell_CursorInteraction::UCPP_AC_Cell_CursorInteraction()
{	
	SMContext = CreateDefaultSubobject<UCPP_SM_Cell_Cursor_Context>(TEXT("CursorSMContext"));
}



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
	

	//OwnerCell->ClickEventDelegate.BindDynamic(this, &UCPP_AC_Cell_CursorInteraction::ClickEvent);
	OwnerCell->UnclickEventDelegate.BindDynamic(this, &UCPP_AC_Cell_CursorInteraction::UnclickEvent);
	OwnerCell->ShiftEventDelegate.BindDynamic(this, &UCPP_AC_Cell_CursorInteraction::ShiftEvent);
}


void UCPP_AC_Cell_CursorInteraction::UnRegisterEventFunctions() const
{
	OwnerCell->OnBeginCursorOver.RemoveDynamic(this, &UCPP_AC_Cell_CursorInteraction::BeginCursorOver);
	OwnerCell->OnEndCursorOver.RemoveDynamic(this, &UCPP_AC_Cell_CursorInteraction::EndCursorOver);
	OwnerCell->OnClicked.RemoveDynamic(this, &UCPP_AC_Cell_CursorInteraction::Clicked);

	//OwnerCell->ClickEventDelegate.Clear();
	OwnerCell->UnclickEventDelegate.Clear();
	OwnerCell->ShiftEventDelegate.Clear();
}



void UCPP_AC_Cell_CursorInteraction::InitComponent()
{
	Super::InitComponent();

	UMaterial* Material = OwnerCell->CellType->CellNormalMaterial;
	MaterialInstance = UMaterialInstanceDynamic::Create(Material, nullptr);
	checkf(MaterialInstance, TEXT("*****> No MaterialInstance (nullptr) <*****"));

	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	OwnerCell->CellStaticMeshComponent->SetMaterial(0, MaterialInstance);
	SMContext->InitStateMachine(OwnerCell, MaterialInstance, World);	
}



void UCPP_AC_Cell_CursorInteraction::BeginCursorOver(AActor* TouchedActor)
{
	SMContext->GetCurrentState()->BeginCursorOver();
}


void UCPP_AC_Cell_CursorInteraction::EndCursorOver(AActor* TouchedActor)
{
	SMContext->GetCurrentState()->EndCursorOver();
}


void UCPP_AC_Cell_CursorInteraction::Clicked(AActor* TouchedComponent, FKey ButtonPressed)
{		
	if (SMContext->GetCurrentState()->Clicked())
	{
		InputEventBus->RaiseClickOnCellEvent(OwnerCell);
	}
	
}


void UCPP_AC_Cell_CursorInteraction::UnclickEvent()
{	
	if (SMContext->GetCurrentState()->ToNormal())
	{
		OwnerCell->NotifyShiftingCanceled();
	}			
}


void UCPP_AC_Cell_CursorInteraction::ShiftEvent(bool ShouldShift)
{
	if (ShouldShift)
	{
		SMContext->GetCurrentState()->Shift();
		return;
	}

	SMContext->GetCurrentState()->ToNormal();	
}

