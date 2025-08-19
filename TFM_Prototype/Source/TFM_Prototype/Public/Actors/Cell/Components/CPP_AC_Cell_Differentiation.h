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

	



private:/*Functions*/

	UFUNCTION()
	void BeginDifferentiateEvent(TSoftObjectPtr<const UCPP_DA_CellType> NewType);


	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void InitComponent() override;

	void RegisterEventFunctions() const;
	void UnRegisterEventFunctions() const;


};
