#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"


#include "CPP_SS_CellsManager.generated.h"



class ACPP_Cell;
class UCPP_DA_GameSettings;
class UCPP_DA_GridSettings;
class ACPP_PlayerController;



UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_CellsManager : public ULocalPlayerSubsystem
{
	GENERATED_BODY()


public:/*Properties*/




public:/*Functions*/

	void ConfigureManager(const UCPP_DA_GameSettings* GameSettingsDA,
		const UCPP_DA_GridSettings* GridSettingsDA, const ACPP_PlayerController* PlayerController);

	void SpawnNewCell();
	





private:/*Properties*/

	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings { nullptr };

	UPROPERTY()
	const UCPP_DA_GridSettings* GridSettings { nullptr };

	UPROPERTY()
	TMap<FVector2f, const ACPP_Cell*> CellsMap;

	UPROPERTY()
	TArray<const ACPP_Cell*> CellsBirthOrder;

	/*UPROPERTY()
	ACPP_Cell* FirstCell { nullptr };*/

	UPROPERTY()
	const ACPP_PlayerController* PlayerContller { nullptr };




private:/*Functions*/

	void AddFirstCell();
	ACPP_Cell* SpawnFirstCell();
	void AddCellSpawned(const ACPP_Cell* NewCell);



};
