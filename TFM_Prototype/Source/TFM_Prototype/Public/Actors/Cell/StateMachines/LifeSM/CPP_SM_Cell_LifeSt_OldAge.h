#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_Life_Base.h"


#include "CPP_SM_Cell_LifeSt_OldAge.generated.h"





UCLASS()
class TFM_PROTOTYPE_API UCPP_SM_Cell_LifeSt_OldAge : public UCPP_SM_Cell_Life_Base
{
	GENERATED_BODY()



public:/*Properties*/




public:/*Functions*/

	virtual void InitState(UCPP_SM_Cell_Context* Context, int StateSortPosition) override;
	virtual void UpdateMaxStateTime() override;


protected:/*Properties*/




protected:/*Functions*/

	const FLinearColor& GetMaterialColor() override;

	
};
