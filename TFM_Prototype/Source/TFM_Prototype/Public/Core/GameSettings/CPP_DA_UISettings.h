#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"


#include "CPP_DA_UISettings.generated.h"





UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_UISettings : public UPrimaryDataAsset
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Tooltip")
	FVector2D TooltipDistaceFromMouse{ FVector2D(10, 10)};
	
};
