#include "EntityCallAvatarBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_AvatarBase::EntityBaseEntityCall_AvatarBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	component1 = new EntityBaseEntityCall_TestBase(16, id);
	component2 = new EntityBaseEntityCall_TestBase(21, id);
	component3 = new EntityBaseEntityCall_TestNoBaseBase(22, id);
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_AvatarBase::~EntityBaseEntityCall_AvatarBase()
{
	if(component1)
		delete component1;

	if(component2)
		delete component2;

	if(component3)
		delete component3;

}



EntityCellEntityCall_AvatarBase::EntityCellEntityCall_AvatarBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	component1 = new EntityCellEntityCall_TestBase(16, id);
	component2 = new EntityCellEntityCall_TestBase(21, id);
	component3 = new EntityCellEntityCall_TestNoBaseBase(22, id);
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_AvatarBase::~EntityCellEntityCall_AvatarBase()
{
	if(component1)
		delete component1;

	if(component2)
		delete component2;

	if(component3)
		delete component3;

}

void EntityCellEntityCall_AvatarBase::dialog(int32 arg1, uint32 arg2)
{
	Bundle* pBundleRet = newCall("dialog", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeInt32(arg1);
	pBundleRet->writeUint32(arg2);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::jump()
{
	Bundle* pBundleRet = newCall("jump", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::relive(uint8 arg1)
{
	Bundle* pBundleRet = newCall("relive", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint8(arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::requestPull()
{
	Bundle* pBundleRet = newCall("requestPull", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::useTargetSkill(int32 arg1, int32 arg2)
{
	Bundle* pBundleRet = newCall("useTargetSkill", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeInt32(arg1);
	pBundleRet->writeInt32(arg2);
	sendCall(NULL);
}


}