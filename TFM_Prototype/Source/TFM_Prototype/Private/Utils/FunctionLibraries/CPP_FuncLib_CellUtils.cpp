#include "Utils/FunctionLibraries/CPP_FuncLib_CellUtils.h"
#include "GameFramework/Character.h"
#include "Utils/Enums/CPPE_NeighbourShortName.h"
#include "Characters/Player/CPP_Player.h"



const FVector2f UCPP_FuncLib_CellUtils::BadAxialLocation{ FVector2f(static_cast<float>(INT_MAX), static_cast<float>(INT_MAX)) };


/**
 * @brief Calculates the world location/rotation of an relative location
	based on player location/rotation 
 * @param Player A pointer to the player character.
 * @param RelativeLocation The relative location from the first cell.
 * @param OutRealLocation The world location.
 * @param OutRealRotation The world rotation.
*/
void UCPP_FuncLib_CellUtils::CalculateWorldLocationRotationBasedOnPlayer(const ACPP_Player* Player,
	const FVector2D RelativeLocation, FVector& OutRealLocation, FRotator& OutRealRotation)
{
	/*if (!CenterCell)
	{
		OutRealLocation = FVector(0, 0, 0);
		return;
	}*/

	OutRealLocation = Player->GetActorLocation();
	OutRealRotation = Player->GetActorRotation();


	if (RelativeLocation == Player->GetRelativeLocation())
	{
		return;
	}

	float Radians = FMath::DegreesToRadians(OutRealRotation.Yaw);
	float SinYaw = FMath::Sin(Radians);
	float CosYaw = FMath::Cos(Radians);

	float Xo = RelativeLocation.X;
	float Yo = RelativeLocation.Y;

	float X = Xo * CosYaw - Yo * SinYaw;
	float Y = Yo * CosYaw + Xo * SinYaw;
	float Z = 0;

	OutRealLocation = FVector(X, Y, Z) + OutRealLocation;
}


/**
 * @brief Calculates the relative location of an destination (axial location)
	from an origin (axial location)
 * @param DistanceBetweenNeighbours Default distance between neighbours.
 * @param OriginAxialLocation An specific axial location.
 * @param DestinationAxialLocation An specific axial location.
 * @param OutRelativeLocation Destination relative location from origin.
*/
void UCPP_FuncLib_CellUtils::GetRelativeLocationFromAnOrigin(float DistanceBetweenNeighbours,
	FVector2f OriginAxialLocation, FVector2f DestinationAxialLocation, FVector2D& OutRelativeLocation)
{
	if (DestinationAxialLocation == OriginAxialLocation)
	{
		OutRelativeLocation = FVector2D(0);
		return;
	}

	float d = DistanceBetweenNeighbours;
	float Delta_q = DestinationAxialLocation.X - OriginAxialLocation.X;
	float Delta_r = DestinationAxialLocation.Y - OriginAxialLocation.Y;

	OutRelativeLocation.X = (d / 2) * Delta_r + d * Delta_q;
	OutRelativeLocation.Y = d * Delta_r * sin60;
}


//FVector2f UCellFunctionLibrary::GetXAxialLocation(FVector2f CurrentAxialLocation, FVector2f OriginAxialLocation)
//{
//	return CurrentAxialLocation + OriginAxialLocation;
//}


/// Checks if two axial locations are next to each other
bool UCPP_FuncLib_CellUtils::AreNeighbours(FVector2f FirstAxialLocation, FVector2f SecondAxialLocation)
{
	return GetDistanceBetweenAxialLocations(FirstAxialLocation, SecondAxialLocation) == 1;
}



int UCPP_FuncLib_CellUtils::GetDistanceBetweenAxialLocations(FVector2f StartAxialLocation, FVector2f EndAxialLocation)
{
	int Dx = EndAxialLocation.X - StartAxialLocation.X;
	int Dy = EndAxialLocation.Y - StartAxialLocation.Y;

	if ((Dx > 0 && Dy > 0) || (Dx < 0 && Dy < 0))
	{
		return FMath::Abs(Dx + Dy);
	}

	Dx = FMath::Abs(Dx);
	Dy = FMath::Abs(Dy);

	return FMath::Max(Dx, Dy);
}



FString UCPP_FuncLib_CellUtils::GetCellOutlinerLabel(FVector2f AxialLocation)
{
	return FString::Printf(TEXT("Cell(%.0f, %.0f)"), AxialLocation.X, AxialLocation.Y);	
}



ECPPE_NeighbourShortName UCPP_FuncLib_CellUtils::GetNeighbourShortName(FVector2f AxialLocation)
{
	if (AxialLocation == FVector2f(1, 0))
	{
		return ECPPE_NeighbourShortName::N;
	}
	if (AxialLocation == FVector2f(0, 1))
	{
		return ECPPE_NeighbourShortName::NE;
	}
	if (AxialLocation == FVector2f(-1, 1))
	{
		return ECPPE_NeighbourShortName::SE;
	}
	if (AxialLocation == FVector2f(-1, 0))
	{
		return ECPPE_NeighbourShortName::S;
	}
	if (AxialLocation == FVector2f(0, -1))
	{
		return ECPPE_NeighbourShortName::SW;
	}
	if (AxialLocation == FVector2f(1, -1))
	{
		return ECPPE_NeighbourShortName::NW;
	}

	return ECPPE_NeighbourShortName::None;
}



FVector2f UCPP_FuncLib_CellUtils::GetAxialLocationByShortName(ECPPE_NeighbourShortName ShortName)
{
	if (ShortName == ECPPE_NeighbourShortName::N)
	{
		return FVector2f(1, 0);
	}
	if (ShortName == ECPPE_NeighbourShortName::NE)
	{
		return FVector2f(0, 1);
	}
	if (ShortName == ECPPE_NeighbourShortName::SE)
	{
		return FVector2f(-1, 1);
	}
	if (ShortName == ECPPE_NeighbourShortName::S)
	{
		return FVector2f(-1, 0);
	}
	if (ShortName == ECPPE_NeighbourShortName::SW)
	{
		return FVector2f(0, -1);
	}
	if (ShortName == ECPPE_NeighbourShortName::NW)
	{
		return FVector2f(1, -1);
	}

	return BadAxialLocation;
}