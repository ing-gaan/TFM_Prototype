#pragma once


UENUM(BlueprintType)
enum class ECPPE_NeighbourShortName : uint8
{
	None,	/// NOT EXIST= Axial(-1, -1) 
	N,	/// North= Axial(1, 0) or Vertex 1 - Triangle(0, 1, 6)
	NE,	/// Northeast= Axial(0, 1) or Vertex 2 - Triangle(0, 2, 1)
	SE,	/// Southeast= Axial(-1, 1) or Vertex 3 - Triangle(0, 3, 2) 
	S,	/// South= Axial(-1, 0) or Vertex 4 - Triangle(0, 4, 3)
	SW,	/// Southwest= Axial(0, -1) or Vertex 5 - Triangle(0, 5, 4)
	NW	/// Northwest= Axial(1, -1) or Vertex 6 - Triangle(0, 6, 5)
};

