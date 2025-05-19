#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CPP_CellsManager.generated.h"



class ACPP_Cell;
class UCPP_DA_GameSettings;
class UCPP_DA_GridSettings;
class ACPP_PlayerController;



UCLASS()
class TFM_PROTOTYPE_API UCPP_CellsManager : public UObject
{
	GENERATED_BODY()
	

public:/*Properties*/

	


public:/*Functions*/

	void InitManager(const UCPP_DA_GameSettings* GameSettingsDA, 
		const UCPP_DA_GridSettings* GridSettingsDA, const ACPP_PlayerController* PlayerController);

	const ACPP_Cell* AddFirstCell();

	void AddCellSpawned(const ACPP_Cell* NewCell);





private:/*Properties*/

	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings {nullptr };

	UPROPERTY()
	const UCPP_DA_GridSettings* GridSettings { nullptr };

	UPROPERTY()
	TMap<FVector2f, const ACPP_Cell*> CellsMap;

	UPROPERTY()
	TArray<const ACPP_Cell*> CellsBirthOrder;

	UPROPERTY()
	ACPP_Cell* FirstCell{ nullptr };

	UPROPERTY()
	const ACPP_PlayerController* PlayerContller{ nullptr };

private:/*Functions*/

	void SpawnFirstCell();

};
