#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"


#include "CPP_SS_CellsManagerEventBus.generated.h"




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFinishCellDivisionEvent, FVector2f, SpawnAxialLocation);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMoveCellsEvent, bool, bCellsMoving);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartCellsShiftingEvent, const ACPP_Cell*, FirstCellToShift);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCellsShiftingReturnEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishCellsShiftingEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBeginDestroyCellEvent, FVector2f, SpawnAxialLocation);




UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_CellsManagerEventBus : public UGameInstanceSubsystem
{
	GENERATED_BODY()



public: /*Properties*/

	UPROPERTY(BlueprintAssignable)
	FFinishCellDivisionEvent FinishCellDivisionEventDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FMoveCellsEvent MoveCellsEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FStartCellsShiftingEvent BeginCellsShiftingEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FCellsShiftingReturnEvent CellsShiftingReturnEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FFinishCellsShiftingEvent FinishCellsShiftingEventDelegate;

	UPROPERTY()
	FBeginDestroyCellEvent BeginDestroyCellEventDelegate;



public: /*Functions*/

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseFinishCellDivisionEvent(FVector2f SpawnAxialLocation)  const
	{
		FinishCellDivisionEventDelegate.Broadcast(SpawnAxialLocation);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseMoveCellsEvent(bool bCellsMoving)  const
	{
		MoveCellsEventDelegate.Broadcast(bCellsMoving);
	}


	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseBeginCellsShiftingEvent(const ACPP_Cell* FirstCellToShift)  const
	{
		BeginCellsShiftingEventDelegate.Broadcast(FirstCellToShift);
	}


	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseCellsShiftingReturnEvent() const
	{
		CellsShiftingReturnEventDelegate.Broadcast();
	}


	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseFinishCellsShiftingEvent() const
	{
		FinishCellsShiftingEventDelegate.Broadcast();

	}


	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseBeginDestroyCellEvent(FVector2f AxialLocation) const
	{
		BeginDestroyCellEventDelegate.Broadcast(AxialLocation);

	}

};
