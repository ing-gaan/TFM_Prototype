#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"



#include "CPP_SS_InputEventBus.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickOnCellEvent, const ACPP_Cell*, Cell);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickOnGridEvent, FVector2f, AxialLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCancelEvent);




class ACPP_Cell;



UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_InputEventBus : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public: /*Properties*/

	UPROPERTY(BlueprintAssignable)
	FClickOnCellEvent ClickOnCellEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FClickOnGridEvent ClickOnGridEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FCancelEvent CancelEventDelegate;



	


public: /*Functions*/
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseClickOnCellEvent(const ACPP_Cell* Cell)
	{
		ClickOnCellEventDelegate.Broadcast(Cell);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseClickOnGridEvent(FVector2f AxialLocation)
	{
		ClickOnGridEventDelegate.Broadcast(AxialLocation);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseCancelEvent()
	{
		CancelEventDelegate.Broadcast();
	}




	
};
