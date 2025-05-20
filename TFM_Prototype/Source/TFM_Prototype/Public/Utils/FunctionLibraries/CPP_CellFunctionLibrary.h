#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"



#include "CPP_CellFunctionLibrary.generated.h"


class ACPP_Player;
enum class ECPP_Neighbours : uint8;


UCLASS()
class TFM_PROTOTYPE_API UCPP_CellFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:

	static constexpr float sin60{ 0.86602540378443864676372317075294 };
	static const FVector2f BadAxialLocation;


	UFUNCTION(BlueprintCallable)
	/**
	 * @brief Calculates the world location/rotation of an relative location
		based on player location/rotation
	 * @param Player A pointer to the player character.
	 * @param RelativeLocation The relative location from the first cell.
	 * @param OutRealLocation The world location.
	 * @param OutRealRotation The world rotation.
	*/
	static void CalculateWorldLocationRotationBasedOnPlayer(const ACPP_Player* Player,
		const FVector2D RelativeLocation, FVector& OutRealLocation, FRotator& OutRealRotation);


	UFUNCTION(BlueprintCallable)
	/**
 * @brief Calculates the relative location of an destination (axial location)
	from an origin (axial location)
 * @param DistanceBetweenNeighbours Default distance between neighbours.
 * @param OriginAxialLocation An specific axial location.
 * @param DestinationAxialLocation An specific axial location.
 * @param OutRelativeLocation Destination relative location from origin.
*/
	static void GetRelativeLocationFromAnOrigin(float DistanceBetweenNeighbours,
		FVector2f OriginAxialLocation, FVector2f DestinationAxialLocation, FVector2D& OutRelativeLocation);



	UFUNCTION(BlueprintCallable)
	/// Checks if two axial locations are next to each other
	static bool AreNeighbours(FVector2f FirstAxialLocation, FVector2f SecondAxialLocation);


	UFUNCTION(BlueprintCallable)
	static int GetDistanceBetweenAxialLocations(FVector2f StartAxialLocation, FVector2f EndAxialLocation);

	static FString GetCellOutlinerLabel(FVector2f AxialLocation);
	static ECPP_Neighbours GetShortNeighbourName(FVector2f AxialLocation);
	static FVector2f GetAxialLocationByShortName(ECPP_Neighbours ShortName);


	template <typename T>
	FORCEINLINE static T GetComponentByName(const AActor* Actor, FString ComponentName)
	{
		TArray<T> Components;
		Actor->GetComponents<T>(Components);

		for (auto& Component : Components)
		{
			if (Component->GetName() == ComponentName)
			{
				return Component;
			}
		}
		return nullptr;
	}
};
