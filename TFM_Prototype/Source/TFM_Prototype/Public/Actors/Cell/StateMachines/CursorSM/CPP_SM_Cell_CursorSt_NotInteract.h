#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Base.h"


#include "CPP_SM_Cell_CursorSt_NotInteract.generated.h"






UCLASS()
class TFM_PROTOTYPE_API UCPP_SM_Cell_CursorSt_NotInteract : public UCPP_SM_Cell_Cursor_Base
{
	GENERATED_BODY()



public:/*Properties*/




public:/*Functions*/

	virtual void SetState() override;

	//--Transition functions
	virtual void ToNormal() override;
	virtual void NoInteract() override;
	virtual void BeginCursorOver() override;
	virtual void EndCursorOver() override;
	virtual void Clicked() override;
	virtual void Shift() override;
	//virtual void Transformed() override;


protected:/*Properties*/




protected:/*Functions*/

	const FLinearColor& GetMaterialColor() override;



	
};
