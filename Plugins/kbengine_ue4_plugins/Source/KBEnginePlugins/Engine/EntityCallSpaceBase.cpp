#include "EntityCallSpaceBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_SpaceBase::EntityBaseEntityCall_SpaceBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_SpaceBase::~EntityBaseEntityCall_SpaceBase()
{
}



EntityCellEntityCall_SpaceBase::EntityCellEntityCall_SpaceBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_SpaceBase::~EntityCellEntityCall_SpaceBase()
{
}


}