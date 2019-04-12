#include "EntityCallSpacesBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_SpacesBase::EntityBaseEntityCall_SpacesBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_SpacesBase::~EntityBaseEntityCall_SpacesBase()
{
}



EntityCellEntityCall_SpacesBase::EntityCellEntityCall_SpacesBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_SpacesBase::~EntityCellEntityCall_SpacesBase()
{
}


}