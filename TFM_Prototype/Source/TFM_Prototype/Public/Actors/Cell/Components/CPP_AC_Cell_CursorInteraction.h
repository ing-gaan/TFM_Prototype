#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Base.h"


#include "CPP_AC_Cell_CursorInteraction.generated.h"




class UCPP_SM_Cell_Cursor_Context;


UCLASS()
class TFM_PROTOTYPE_API UCPP_AC_Cell_CursorInteraction : public UCPP_AC_Cell_Base
{
	GENERATED_BODY()


public:
	UCPP_AC_Cell_CursorInteraction();



public:/*Properties*/



public:/*Functions*/

	//--Transition functions
	//virtual void ToNormal() override;
	//virtual void NoInteract() override;
	//virtual void BeginCursorOver() override;
	//virtual void Clicked() override;
	//virtual void Shift() override;
	//virtual void Transformed() override;



protected:/*Properties*/

	UPROPERTY()
	UCPP_SM_Cell_Cursor_Context* SMContext{ nullptr };

	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstance{ nullptr };





protected:/*Functions*/

	UFUNCTION()
	void BeginCursorOver(AActor* TouchedActor);
	
	UFUNCTION()
	void EndCursorOver(AActor* TouchedActor);

	UFUNCTION()
	void Clicked(AActor* TouchedComponent, FKey ButtonPressed);

	UFUNCTION()
	void UnclickEvent();

	UFUNCTION()
	void ShiftEvent(bool ShouldShift);

	/*UFUNCTION()
	void FinishCellDivisionEvent(FVector2f SpawnAxialLocation);*/




	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RegisterEventFunctions() const;
	void UnRegisterEventFunctions() const;

	virtual void InitComponent() override;

	//void SetMaterialColorParameter(const FLinearColor& MaterialColor);

};
