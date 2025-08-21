#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"


#include "CPPI_Tooltipable.generated.h"




UINTERFACE(MinimalAPI, Blueprintable)
class UCPPI_Tooltipable : public UInterface
{
	GENERATED_BODY()
};


class TFM_PROTOTYPE_API ICPPI_Tooltipable
{
	GENERATED_BODY()



public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FText GetTooltipText() const;


};
