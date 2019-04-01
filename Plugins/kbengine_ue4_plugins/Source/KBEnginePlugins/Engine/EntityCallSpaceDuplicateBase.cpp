#include "EntityCallSpaceDuplicateBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_SpaceDuplicateBase::EntityBaseEntityCall_SpaceDuplicateBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_SpaceDuplicateBase::~EntityBaseEntityCall_SpaceDuplicateBase()
{
}



EntityCellEntityCall_SpaceDuplicateBase::EntityCellEntityCall_SpaceDuplicateBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_SpaceDuplicateBase::~EntityCellEntityCall_SpaceDuplicateBase()
{
}


}