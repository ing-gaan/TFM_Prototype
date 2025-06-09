#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Base.h"


#include "CPP_AC_Cell_CursorInteraction.generated.h"







UCLASS()
class TFM_PROTOTYPE_API UCPP_AC_Cell_CursorInteraction : public UCPP_AC_Cell_Base
{
	GENERATED_BODY()


public:/*Properties*/



public:/*Functions*/



protected:/*Properties*/

	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstance;





protected:/*Functions*/

	UFUNCTION()
	void BeginCursorOver(AActor* TouchedActor);
	
	UFUNCTION()
	void EndCursorOver(AActor* TouchedActor);

	UFUNCTION()
	void ClickEvent();

	UFUNCTION()
	void UnclickEvent();

	/*UFUNCTION()
	void FinishCellDivisionEvent(FVector2f SpawnAxialLocation);*/




	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RegisterEventFunctions() const;
	void UnRegisterEventFunctions() const;

	virtual void InitComponent() override;

	void SetMaterialColorParameter(const FLinearColor& MaterialColor);

};
