#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"


#include "CPP_DA_WidgetClasses.generated.h"



class UCPP_W_Base;


UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_WidgetClasses : public UPrimaryDataAsset
{
	GENERATED_BODY()



public:/*Properties*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<TSubclassOf<UCPP_W_Base>> WidgetClasses;



	
};
