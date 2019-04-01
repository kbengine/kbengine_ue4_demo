#include "EntityCallGateBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_GateBase::EntityBaseEntityCall_GateBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_GateBase::~EntityBaseEntityCall_GateBase()
{
}



EntityCellEntityCall_GateBase::EntityCellEntityCall_GateBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_GateBase::~EntityCellEntityCall_GateBase()
{
}


}