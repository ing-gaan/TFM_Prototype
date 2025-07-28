#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Base.h"


#include "CPP_SM_Cell_CursorSt_Clicked.generated.h"






UCLASS()
class TFM_PROTOTYPE_API UCPP_SM_Cell_CursorSt_Clicked : public UCPP_SM_Cell_Cursor_Base
{
	GENERATED_BODY()



public:/*Properties*/




public:/*Functions*/

	virtual void SetState() override;

	//--Transition functions
	virtual bool ToNormal() override;
	virtual bool NoInteract() override;
	virtual bool BeginCursorOver() override;
	//virtual bool EndCursorOver() override;
	//virtual bool Clicked() override;
	//virtual bool Shift() override;
	//virtual bool Transformed() override;


protected:/*Properties*/




protected:/*Functions*/

	const FLinearColor& GetMaterialColor() override;



	
};
