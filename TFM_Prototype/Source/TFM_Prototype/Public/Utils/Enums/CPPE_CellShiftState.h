#pragma once


UENUM(BlueprintType)
enum class ECPPE_CellShiftState : uint8
{
	None,				/// No state - Error
	AtOriginLocation,	/// The cell stays at the origin axial location.
	AtTempLocation,		/// The cell stays at the temporal axial location.
	ShiftingToOrigin,	/// The cell is moving to origin axial location. 
	ShiftingToTemp,		/// The cell is moving to temporal axial location. 
};