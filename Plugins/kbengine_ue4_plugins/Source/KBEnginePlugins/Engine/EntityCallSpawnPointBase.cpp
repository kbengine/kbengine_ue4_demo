#include "EntityCallSpawnPointBase.h"
#include "Bundle.h"


EntityBaseEntityCall_SpawnPointBase::EntityBaseEntityCall_SpawnPointBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_SpawnPointBase::~EntityBaseEntityCall_SpawnPointBase()
{
}



EntityCellEntityCall_SpawnPointBase::EntityCellEntityCall_SpawnPointBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_SpawnPointBase::~EntityCellEntityCall_SpawnPointBase()
{
}

