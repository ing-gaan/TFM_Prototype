#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"


#include "CPP_DA_WidgetClasses.generated.h"





UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_WidgetClasses : public UPrimaryDataAsset
{
	GENERATED_BODY()



public:/*Properties*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<TSubclassOf<UUserWidget>> WidgetClasses;



	
};
