#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"


#include "CPP_Player.generated.h"



class UCPP_DA_GridSettings;
class UCPP_DA_GameSettings;
class UCPP_DA_CameraSettings;
class USpringArmComponent;
class UCameraComponent;
class ACPP_Cell;
class USphereComponent;




UCLASS()
class TFM_PROTOTYPE_API ACPP_Player : public APawn
{
	GENERATED_BODY()

public:	
	ACPP_Player();


public:/*Properties*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACPP_Cell* PhantomCell{ nullptr };

	



public:/*Functions*/

	UFUNCTION(BlueprintCallable)
	FVector2f GetAxialLocation() const;

	UFUNCTION(BlueprintCallable)
	void SetAxialLocation(FVector2f NewAxialLocation);

	UFUNCTION(BlueprintCallable)
	FVector2D GetRelativeLocation() const;

	UFUNCTION(BlueprintCallable)
	void SetSphereCollisionRadius(int Radius);


protected:/*Properties*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector2f AxialLocation{ FVector2f(0, 0) };

	UPROPERTY()
	FVector2D RelativeLocation{ FVector2D(0, 0) };

	UPROPERTY()
	const UCPP_DA_GridSettings* GridSettings { nullptr };

	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings { nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereCollision;


protected:/*Functions*/



	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	void InitPlayer();

	

};
