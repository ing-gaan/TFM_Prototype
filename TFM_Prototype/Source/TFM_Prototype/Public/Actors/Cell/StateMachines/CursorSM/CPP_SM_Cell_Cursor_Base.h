#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "CPP_SM_Cell_Cursor_Base.generated.h"



class UCPP_SM_Cell_Cursor_Context;



UCLASS()
class TFM_PROTOTYPE_API UCPP_SM_Cell_Cursor_Base : public UObject
{
	GENERATED_BODY()



public:/*Properties*/




public:/*Functions*/

	virtual void InitializeState(UCPP_SM_Cell_Cursor_Context* Context);
	virtual void SetState();
	

	//--Transition functions
	virtual void ToNormal();
	virtual void NoInteract();
	virtual void BeginCursorOver();
	virtual void EndCursorOver();
	virtual void Clicked();
	virtual void Shift();
	//virtual void Transformed();
	


protected:/*Properties*/

	UPROPERTY()
	UCPP_SM_Cell_Cursor_Context* SMContext{ nullptr };


protected:/*Functions*/

	virtual const FLinearColor& GetMaterialColor();
	void SetMaterialColorParameter(const FLinearColor& MaterialColor);


	
};
