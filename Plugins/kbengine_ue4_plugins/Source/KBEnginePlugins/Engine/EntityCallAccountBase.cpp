#include "EntityCallAccountBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_AccountBase::EntityBaseEntityCall_AccountBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_AccountBase::~EntityBaseEntityCall_AccountBase()
{
}

void EntityBaseEntityCall_AccountBase::reqAvatarList()
{
	Bundle* pBundleRet = newCall("reqAvatarList", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqCreateAvatar(uint8 arg1, const FString& arg2)
{
	Bundle* pBundleRet = newCall("reqCreateAvatar", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint8(arg1);
	pBundleRet->writeUnicode(arg2);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqRemoveAvatar(const FString& arg1)
{
	Bundle* pBundleRet = newCall("reqRemoveAvatar", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUnicode(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqRemoveAvatarDBID(uint64 arg1)
{
	Bundle* pBundleRet = newCall("reqRemoveAvatarDBID", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint64(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::selectAvatarGame(uint64 arg1)
{
	Bundle* pBundleRet = newCall("selectAvatarGame", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint64(arg1);
	sendCall(NULL);
}



EntityCellEntityCall_AccountBase::EntityCellEntityCall_AccountBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_AccountBase::~EntityCellEntityCall_AccountBase()
{
}


}