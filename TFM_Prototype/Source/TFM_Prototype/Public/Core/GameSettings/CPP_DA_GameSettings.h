#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"



#include "CPP_DA_GameSettings.generated.h"



class ACPP_Cell;


UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_GameSettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Timers", 
		meta = (ToolTip = "", ClampMin = 0, ForceUnits = "Seconds"))
	float StartCellsManagerAfter{ 1 };


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Locations")
	float DefaultHeightFromGround{ 10 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Locations")
	float HiddenHeightFromGround{ -100 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Cells|Types")
	TSubclassOf<ACPP_Cell> FirstCellBPClass{ nullptr };






	
};
