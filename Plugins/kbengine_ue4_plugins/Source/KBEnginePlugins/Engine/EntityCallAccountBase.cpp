#include "EntityCallAccountBase.h"
#include "Bundle.h"

namespace KBEngine
{

void EntityBaseEntityCall_AccountBase::reqAvatarList()
{
	Bundle* pBundle = newCall("reqAvatarList");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqCreateAvatar(uint8 arg1, const FString& arg2)
{
	Bundle* pBundle = newCall("reqCreateAvatar");
	if(!pBundle)
		return;

	pBundle->writeUint8(arg1);
	pBundle->writeUnicode(arg2);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqRemoveAvatar(const FString& arg1)
{
	Bundle* pBundle = newCall("reqRemoveAvatar");
	if(!pBundle)
		return;

	pBundle->writeUnicode(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqRemoveAvatarDBID(uint64 arg1)
{
	Bundle* pBundle = newCall("reqRemoveAvatarDBID");
	if(!pBundle)
		return;

	pBundle->writeUint64(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::selectAvatarGame(uint64 arg1)
{
	Bundle* pBundle = newCall("selectAvatarGame");
	if(!pBundle)
		return;

	pBundle->writeUint64(arg1);
	sendCall(NULL);
}



}