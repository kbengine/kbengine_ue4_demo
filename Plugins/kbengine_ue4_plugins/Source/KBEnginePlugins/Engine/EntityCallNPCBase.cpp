#include "EntityCallNPCBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_NPCBase::EntityBaseEntityCall_NPCBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_NPCBase::~EntityBaseEntityCall_NPCBase()
{
}



EntityCellEntityCall_NPCBase::EntityCellEntityCall_NPCBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_NPCBase::~EntityCellEntityCall_NPCBase()
{
}


}