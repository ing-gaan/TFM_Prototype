#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"



#include "CPP_SS_InputEventBus.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickOnCellEvent, const ACPP_Cell*, Cell);



class ACPP_Cell;



UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_InputEventBus : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public: /*Properties*/

	UPROPERTY(BlueprintAssignable)
	FClickOnCellEvent ClickOnCellEventDelegate;






public: /*Functions*/

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseClickOnCellEvent(const ACPP_Cell* Cell)
	{
		ClickOnCellEventDelegate.Broadcast(Cell);
	}




protected:







private:



	
};
