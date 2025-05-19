#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "CPP_Cell.generated.h"



class UCPP_DA_GridSettings;
class ACPP_PlayerController;
class UCPP_DA_CellType;
class ACPP_Player;




UCLASS()
class TFM_PROTOTYPE_API ACPP_Cell : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPP_Cell();
	//friend class ACPP_PlayerController;



public: /*Properties*/

	UPROPERTY()
	const ACPP_PlayerController* PlayerController{ nullptr };

	UPROPERTY()
	const ACPP_Player* Player{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_GridSettings* GridSettings { nullptr };
	
	UPROPERTY()
	const UCPP_DA_CellType* CellType;





public: /*Functions*/

	UFUNCTION(BlueprintCallable)
	FVector2f GetAxialLocation() const;

	UFUNCTION(BlueprintCallable)
	void SetAxialLocation(FVector2f NewAxialLocation);

	UFUNCTION(BlueprintCallable)
	FVector2D GetRelativeLocation() const;

	





protected: /*Properties*/
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector2f AxialLocation{ FVector2f(0, 0) };

	UPROPERTY()
	FVector2D RelativeLocation{ FVector2D(0, 0) };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsCellMoving{false};



protected: /*Functions*/

	UFUNCTION(BlueprintCallable)
	void SetRelativeLocation();


	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	void MoveCell();




	
};
