#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CPP_DA_CellType.generated.h"



class UCPP_AC_Cell_Base;



UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_CellType : public UPrimaryDataAsset
{
	GENERATED_BODY()


public:/*Properties*/

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Basics")
	UStaticMesh* CellStaticMesh{ nullptr };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Colors")
	FLinearColor NormalColor { FLinearColor::White };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Colors")
	FLinearColor CursorOverColor{ FLinearColor::White };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Colors")
	FLinearColor ClickedColor{ FLinearColor::White };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Materials")
	UMaterial* CellNormalMaterial { nullptr };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Materials")
	FName MaterialColorParameterName { };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties|Necessary actor components")
	TSet<TSubclassOf<UCPP_AC_Cell_Base>> NecessaryCellComponents;
	
	

public:/*Functions*/
	
};
