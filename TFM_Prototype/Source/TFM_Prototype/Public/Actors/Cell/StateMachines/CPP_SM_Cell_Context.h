#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "CPP_SM_Cell_Context.generated.h"


class ACPP_Cell;



UCLASS()
class TFM_PROTOTYPE_API UCPP_SM_Cell_Context : public UObject
{
	GENERATED_BODY()



public:/*Properties*/

	UPROPERTY()
	const UWorld* World;

	UPROPERTY()
	ACPP_Cell* OwnerCell{ nullptr };

	UPROPERTY()
	UMaterialInstanceDynamic* CellMaterialInstance{ nullptr };

	UPROPERTY()
	FLinearColor CurrentCellColor;



public:/*Functions*/

	virtual void InitStateMachine(ACPP_Cell* Cell, UMaterialInstanceDynamic* MaterialInstance, const UWorld* GameWorld);




protected:/*Properties*/
	
	



protected:/*Functions*/



};
