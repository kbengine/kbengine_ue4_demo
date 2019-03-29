#include "EntityCallTestBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_TestBase::EntityBaseEntityCall_TestBase(uint16 ecpID, int32 eid) : 
EntityCall(eid, "Test"),
entityComponentPropertyID(0)
{
	entityComponentPropertyID = ecpID;
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_TestBase::~EntityBaseEntityCall_TestBase()
{
}

void EntityBaseEntityCall_TestBase::say(int32 arg1)
{
	Bundle* pBundleRet = newCall("say", entityComponentPropertyID);
	if(!pBundleRet)
		return;

	pBundleRet->writeInt32(arg1);
	sendCall(NULL);
}



EntityCellEntityCall_TestBase::EntityCellEntityCall_TestBase(uint16 ecpID, int32 eid) : 
EntityCall(eid, "Test"),
entityComponentPropertyID(0)
{
	entityComponentPropertyID = ecpID;
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_TestBase::~EntityCellEntityCall_TestBase()
{
}

void EntityCellEntityCall_TestBase::hello(int32 arg1)
{
	Bundle* pBundleRet = newCall("hello", entityComponentPropertyID);
	if(!pBundleRet)
		return;

	pBundleRet->writeInt32(arg1);
	sendCall(NULL);
}


}