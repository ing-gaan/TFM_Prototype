#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Base.h"


#include "CPP_AC_Cell_Differentiation.generated.h"



class UCPP_DA_CellType;


UCLASS()
class TFM_PROTOTYPE_API UCPP_AC_Cell_Differentiation : public UCPP_AC_Cell_Base
{
	GENERATED_BODY()


public:/*Properties*/


public:/*Functions*/






private:/*Properties*/

	UFUNCTION()
	bool DifferentiateEvent(const UCPP_DA_CellType* NewType);



private:/*Functions*/

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void InitComponent() override;

	void RegisterEventFunctions() const;
	void UnRegisterEventFunctions() const;
	

};
