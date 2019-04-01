#include "EntityCallTestNoBaseBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_TestNoBaseBase::EntityBaseEntityCall_TestNoBaseBase(uint16 ecpID, int32 eid) : 
EntityCall(eid, "TestNoBase"),
entityComponentPropertyID(0)
{
	entityComponentPropertyID = ecpID;
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_TestNoBaseBase::~EntityBaseEntityCall_TestNoBaseBase()
{
}



EntityCellEntityCall_TestNoBaseBase::EntityCellEntityCall_TestNoBaseBase(uint16 ecpID, int32 eid) : 
EntityCall(eid, "TestNoBase"),
entityComponentPropertyID(0)
{
	entityComponentPropertyID = ecpID;
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_TestNoBaseBase::~EntityCellEntityCall_TestNoBaseBase()
{
}

void EntityCellEntityCall_TestNoBaseBase::hello(int32 arg1)
{
	Bundle* pBundleRet = newCall("hello", entityComponentPropertyID);
	if(!pBundleRet)
		return;

	pBundleRet->writeInt32(arg1);
	sendCall(NULL);
}


}