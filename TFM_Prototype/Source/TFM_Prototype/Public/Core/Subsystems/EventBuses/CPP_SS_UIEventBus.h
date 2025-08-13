#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"


#include "CPP_SS_UIEventBus.generated.h"




DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginCellDivisionEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginCellDifferentiationEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFinishCellDifferentiationEvent, const UCPP_DA_CellType*, NewCellType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginEliminateCellEvent);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishDestroyCellEvent);



UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_UIEventBus : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public: /*Properties*/

	UPROPERTY(BlueprintAssignable)
	FBeginCellDivisionEvent BeginCellDivisionEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FBeginCellDifferentiationEvent BeginCellDifferentiationEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FFinishCellDifferentiationEvent FinishCellDifferentiationEventDelegate;

	UPROPERTY()
	FBeginEliminateCellEvent BeginEliminateCellEventDelegate;





public: /*Functions*/

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseBeginCellDivisionEvent()
	{
		BeginCellDivisionEventDelegate.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseBeginCellDifferentiationEvent()
	{
		BeginCellDifferentiationEventDelegate.Broadcast();
	}
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseFinishCellDifferentiationEvent(const UCPP_DA_CellType* NewCellType)
	{
		FinishCellDifferentiationEventDelegate.Broadcast(NewCellType);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseBeginEliminateCellEvent()
	{
		BeginEliminateCellEventDelegate.Broadcast();
	}







};
