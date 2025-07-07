#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CPP_FuncLib_AStarSearch.generated.h"



class ACPP_Cell;


USTRUCT()
struct FASearchNode
{
	GENERATED_USTRUCT_BODY()

	FASearchNode();
	FASearchNode(int G, int H, FVector2f ParentLocation, FVector2f AxialLocation);

	int G;
	int H;
	int F;
	FVector2f ParentLocation;
	FVector2f AxialLocation;
};



UCLASS()
class TFM_PROTOTYPE_API UCPP_FuncLib_AStarSearch : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
	//PROPERTIES


	//FUNCTIONS
	static bool CalculatePath(const TMap<FVector2f, const ACPP_Cell*>* CellsMap, const TArray<FVector2f>* InitAxialLocations,
		FVector2f StartAxialLocation, FVector2f EndAxialLocation, TArray<FVector2f>& OutPath, int& OutPathCost);


private:
	//PROPERTIES
	inline static TMap<FVector2f, FASearchNode> LikelyNodes;
	inline static TMap<FVector2f, FASearchNode> ChosenNodes;
	inline static FVector2f StartLocation{ FVector2f(0, 0) };
	inline static FVector2f EndLocation{ FVector2f(0, 0) };
	inline static bool bWasPathFound{ false };


	//FUNCTIONS
	static void Init(FVector2f StartAxialLocation, FVector2f EndAxialLocation, TArray<FVector2f>& OutPath);
	static bool WouldThereBeValidPath(const TMap<FVector2f, const ACPP_Cell*>* CellsMap, const TArray<FVector2f>* InitAxialLocations);
	static bool AddLikelyNodes(const TMap<FVector2f, const ACPP_Cell*>* CellsMap,
		const TArray<FVector2f>* InitAxialLocations, FASearchNode ParentNode);
	static bool CanBeIncluded(const ACPP_Cell* const* Cell, FVector2f NeighbourLocation);
	static void AddOrModifyLikelyNode(const ACPP_Cell* Cell, FVector2f NeighbourLocation, FASearchNode ParentNode);
	static FASearchNode ChoseBetterNextNode();
	static void BuildPath(FASearchNode LastChosenNode, TArray<FVector2f>& OutPath);
};
