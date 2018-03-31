#include "EntityCallAvatarBase.h"
#include "Bundle.h"


void EntityCellEntityCall_AvatarBase::dialog(int32 arg1, uint32 arg2)
{
	Bundle* pBundle = newCall("dialog");
	if(!pBundle)
		return;

	pBundle->writeInt32(arg1);
	pBundle->writeUint32(arg2);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::jump()
{
	Bundle* pBundle = newCall("jump");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::relive(uint8 arg1)
{
	Bundle* pBundle = newCall("relive");
	if(!pBundle)
		return;

	pBundle->writeUint8(arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::requestPull()
{
	Bundle* pBundle = newCall("requestPull");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::useTargetSkill(int32 arg1, int32 arg2)
{
	Bundle* pBundle = newCall("useTargetSkill");
	if(!pBundle)
		return;

	pBundle->writeInt32(arg1);
	pBundle->writeInt32(arg2);
	sendCall(NULL);
}

