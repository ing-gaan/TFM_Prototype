#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"


#include "CPP_Player.generated.h"



class UCPP_DA_GridSettings;
class UCPP_DA_GameSettings;


UCLASS()
class TFM_PROTOTYPE_API ACPP_Player : public APawn
{
	GENERATED_BODY()

public:	
	ACPP_Player();


public:/*Properties*/




public:/*Functions*/

	UFUNCTION(BlueprintCallable)
	FVector2f GetAxialLocation() const;

	UFUNCTION(BlueprintCallable)
	void SetAxialLocation(FVector2f NewAxialLocation);

	UFUNCTION(BlueprintCallable)
	FVector2D GetRelativeLocation() const;





protected:/*Properties*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector2f AxialLocation{ FVector2f(0, 0) };

	UPROPERTY()
	FVector2D RelativeLocation{ FVector2D(0, 0) };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_GridSettings* GridSettings { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_GameSettings* GameSettings { nullptr };


protected:/*Functions*/



	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;




	

};
