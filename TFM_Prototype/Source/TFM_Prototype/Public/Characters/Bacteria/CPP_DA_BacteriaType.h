#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"


#include "CPP_DA_BacteriaType.generated.h"



enum class ECPPE_BacteriaType : uint8;



UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_BacteriaType : public UPrimaryDataAsset
{
	GENERATED_BODY()




public:/*Properties*/


	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Data")
	ECPPE_BacteriaType BacteriaType;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Basics")
	UStaticMesh* BacteriaStaticMesh{ nullptr };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Basics")
	UMaterialInterface* BacteriaMaterial{ nullptr };



	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties|Basics",
		meta = (ToolTip = "", ClampMin = 0, Units = "Percent"))
	FVector MeshScale{ FVector(1.0, 1.0, 1.0) };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties|Basics",
		meta = (ToolTip = "", ClampMin = 0))
	float MaxLifePoints{ 100 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties|Basics",
		meta = (ToolTip = "", ClampMin = 0, Units = "Percent"))
	float InitMinPercentLife{ 100 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties|Basics",
		meta = (ToolTip = "", ClampMin = 0, Units = "Percent"))
	float InitMaxPercentLife{ 100 };
	
};
