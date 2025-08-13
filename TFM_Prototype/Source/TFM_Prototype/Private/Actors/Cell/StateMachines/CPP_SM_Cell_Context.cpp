#include "Actors/Cell/StateMachines/CPP_SM_Cell_Context.h"




void UCPP_SM_Cell_Context::InitStateMachine(ACPP_Cell* Cell, UMaterialInstanceDynamic* MaterialInstance, const UWorld* GameWorld)
{
	OwnerCell = Cell;
	CellMaterialInstance = MaterialInstance;
	World = GameWorld;
}