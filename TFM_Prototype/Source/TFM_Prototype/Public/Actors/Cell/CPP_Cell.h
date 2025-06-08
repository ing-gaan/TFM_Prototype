#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "CPP_Cell.generated.h"




class UCPP_DA_GridSettings;
class UCPP_DA_GameSettings;
class ACPP_PlayerController;
class UCPP_DA_CellType;
class ACPP_Player;
class UCPP_AC_Cell_Base;




DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(ACPP_Cell*, FDivideEvent, FVector2f, NewAxialLocation);
DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FDifferentiateEvent, const UCPP_DA_CellType*, Newtype);



UCLASS()
class TFM_PROTOTYPE_API ACPP_Cell : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPP_Cell();
	//friend class ACPP_PlayerController;



public: /*Properties*/

	UPROPERTY()
	FDivideEvent DivideEventDelegate;

	UPROPERTY()
	FDifferentiateEvent DifferentiateEventDelegate;



	UPROPERTY()
	const ACPP_PlayerController* PlayerController{ nullptr };

	UPROPERTY()
	const ACPP_Player* Player{ nullptr };

	UPROPERTY()
	const UCPP_DA_GridSettings* GridSettings{ nullptr };

	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings{ nullptr };
	
	UPROPERTY()
	const UCPP_DA_CellType* CellType;
	

	UPROPERTY()
	UStaticMeshComponent* CellStaticMeshComponent{ nullptr };



public: /*Functions*/

	UFUNCTION(BlueprintCallable)
	FVector2f GetAxialLocation() const;

	UFUNCTION(BlueprintCallable)
	void SetAxialLocation(FVector2f NewAxialLocation);

	UFUNCTION(BlueprintCallable)
	FVector2D GetRelativeLocation() const;

	UFUNCTION()
	ACPP_Cell* Divide(FVector2f NewAxialLocation) const;

	UFUNCTION()
	bool Differentiate(const UCPP_DA_CellType* Newtype) const;

	UFUNCTION()
	bool HasThisAbility(TSubclassOf<UCPP_AC_Cell_Base> Ability) const;

	UFUNCTION()
	bool LoadCellTypeComponents(const UCPP_DA_CellType* NewCellType);




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

	void RegisterEventFunctions() const;
	void UnRegisterEventFunctions() const;

	void InitCell();
	//void LoadStaticMeshComponent();
	


	void MoveCell();

	
	
	
};
