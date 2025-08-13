#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/StateMachines/CPP_SM_Cell_Context.h"


#include "CPP_SM_Cell_Cursor_Context.generated.h"



class ACPP_Cell;
class UCPP_SM_Cell_Cursor_Base;




UCLASS()
class TFM_PROTOTYPE_API UCPP_SM_Cell_Cursor_Context : public UCPP_SM_Cell_Context
{
	GENERATED_BODY()


public:/*Properties*/

	


public:/*Functions*/

	virtual void InitStateMachine(ACPP_Cell* Cell, UMaterialInstanceDynamic* MaterialInstance, const UWorld* GameWorld) override;
	UCPP_SM_Cell_Cursor_Base* GetCurrentState();
	


protected:/*Properties*/

	UPROPERTY()
	TMap<TSubclassOf<UCPP_SM_Cell_Cursor_Base>, UCPP_SM_Cell_Cursor_Base*> States;

	UPROPERTY()
	UCPP_SM_Cell_Cursor_Base* CurrentState{ nullptr };

	bool bIsInitialized{ false };




protected:/*Functions*/

	void ChangeState(TSubclassOf<UCPP_SM_Cell_Cursor_Base> NewStateType);



	friend class UCPP_SM_Cell_CursorSt_Clicked;
	friend class UCPP_SM_Cell_CursorSt_Init;
	friend class UCPP_SM_Cell_CursorSt_Normal;
	friend class UCPP_SM_Cell_CursorSt_NotInteract;
	friend class UCPP_SM_Cell_CursorSt_Over;
	friend class UCPP_SM_Cell_CursorSt_Shifting;


	
};
