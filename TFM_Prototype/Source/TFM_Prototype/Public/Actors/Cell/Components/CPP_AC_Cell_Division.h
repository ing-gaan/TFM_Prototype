#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Base.h"


#include "CPP_AC_Cell_Division.generated.h"





UCLASS()
class TFM_PROTOTYPE_API UCPP_AC_Cell_Division : public UCPP_AC_Cell_Base
{
	GENERATED_BODY()



public:/*Properties*/


public:/*Functions*/

	




private:/*Properties*/

	UFUNCTION()
	ACPP_Cell* DivideEvent(FVector2f AxialLocation);


	ACPP_Cell* SpawnCell(FVector CellLocation, FRotator CellRotation, TSubclassOf<ACPP_Cell> CellClass);
	void ConfigureNewCell(ACPP_Cell* NewCell, FVector2f AxialLocation);


private:/*Functions*/

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void InitComponent() override;

	void RegisterEventFunctions() const;
	void UnRegisterEventFunctions() const;
	
};
