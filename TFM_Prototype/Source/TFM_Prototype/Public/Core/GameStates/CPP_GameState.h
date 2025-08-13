#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"


#include "CPP_GameState.generated.h"



class UCPP_SS_TimeEventBus;


UCLASS()
class TFM_PROTOTYPE_API ACPP_GameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ACPP_GameState();




public: /*Properties*/


public: /*Functions*/




protected: /*Properties*/

	UPROPERTY()
	UWorld* World{ nullptr };
	UPROPERTY()
	const UCPP_SS_TimeEventBus* TimeEventBus { nullptr };

	int SecondsPassed{ 0 };
	int TensMilliSecondsPassed{ 0 };



protected: /*Functions*/

	UFUNCTION()
	void TenMilliSecondsPassed();
	UFUNCTION()
	void OneSecondPassed();

	virtual void BeginPlay() override;

	void InitGameState();
	void StartTenMilliSecondsTimer();

	
};
