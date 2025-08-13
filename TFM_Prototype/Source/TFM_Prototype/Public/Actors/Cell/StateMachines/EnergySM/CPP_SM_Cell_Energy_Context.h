#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/StateMachines/CPP_SM_Cell_Context.h"


#include "CPP_SM_Cell_Energy_Context.generated.h"



class UCPP_SM_Cell_Energy_Base;
class ACPP_Cell;



UCLASS()
class TFM_PROTOTYPE_API UCPP_SM_Cell_Energy_Context : public UCPP_SM_Cell_Context
{
	GENERATED_BODY()


public:/*Properties*/

	UPROPERTY()
	UCPP_SM_Cell_Energy_Base* CurrentState{ nullptr };
	



public:/*Functions*/

	virtual void InitStateMachine(ACPP_Cell* Cell, UMaterialInstanceDynamic* MaterialInstance, const UWorld* GameWorld) override;
	void CheckEnergyState();



protected:/*Properties*/

	UPROPERTY()
	TMap<TSubclassOf<UCPP_SM_Cell_Energy_Base>, UCPP_SM_Cell_Energy_Base*> States;




protected:/*Functions*/



	
};
