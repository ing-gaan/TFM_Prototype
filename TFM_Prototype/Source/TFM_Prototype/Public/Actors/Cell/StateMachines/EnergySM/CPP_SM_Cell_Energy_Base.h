#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/StateMachines/CPP_SM_Cell_Base.h"


#include "CPP_SM_Cell_Energy_Base.generated.h"



class UCPP_SM_Cell_Energy_Context;



UCLASS()
class TFM_PROTOTYPE_API UCPP_SM_Cell_Energy_Base : public UCPP_SM_Cell_Base
{
	GENERATED_BODY()


public:/*Properties*/




public:/*Functions*/

	virtual void InitializeState(UCPP_SM_Cell_Context* Context) override;
	virtual void ImplementState() override;

protected:/*Properties*/

	UPROPERTY()
	UCPP_SM_Cell_Energy_Context* SMContext{ nullptr };
	


protected:/*Functions*/

	const FLinearColor& GetMaterialColor() override;


	
};
