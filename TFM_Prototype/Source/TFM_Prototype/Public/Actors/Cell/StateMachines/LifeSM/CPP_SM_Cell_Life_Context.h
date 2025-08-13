#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/StateMachines/CPP_SM_Cell_Context.h"


#include "CPP_SM_Cell_Life_Context.generated.h"



class UCPP_SM_Cell_Life_Base;
class ACPP_Cell;



UCLASS()
class TFM_PROTOTYPE_API UCPP_SM_Cell_Life_Context : public UCPP_SM_Cell_Context
{
	GENERATED_BODY()


public:/*Properties*/

	UPROPERTY()
	UCPP_SM_Cell_Life_Base* CurrentState{ nullptr };




public:/*Functions*/

	virtual void InitStateMachine(ACPP_Cell* Cell, UMaterialInstanceDynamic* MaterialInstance, const UWorld* GameWorld) override;
	//void InitContext(ACPP_Cell* Cell);
	void ChangeState();
	void ChangeState(TSubclassOf<UCPP_SM_Cell_Life_Base> NewStateType);
	int GetStateSortPosition(TSubclassOf<UCPP_SM_Cell_Life_Base> StateType);
	void ChangeToNewCellTypeStates();


protected:/*Properties*/

	UPROPERTY()
	TArray<UCPP_SM_Cell_Life_Base*> States;

	int CurrentStateId{ 0 };




protected:/*Functions*/

	UCPP_SM_Cell_Life_Base* GetState(TSubclassOf<UCPP_SM_Cell_Life_Base> StateType);

	
};
