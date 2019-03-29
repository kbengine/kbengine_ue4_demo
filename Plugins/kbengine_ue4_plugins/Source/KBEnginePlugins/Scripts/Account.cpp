#include "Account.h"
#include "Engine/Entity.h"
#include "Engine/KBEngine.h"
#include "Engine/KBDebug.h"
#include "LogicEvents.h"

namespace KBEngine
{

Account::Account():
	AccountBase(),
	characters()
{
}

Account::~Account()
{
}

void Account::__init__()
{
	// 注册事件
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("reqCreateAvatar", "reqCreateAvatar", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqCreateAvatar& data = static_cast<const UKBEventData_reqCreateAvatar&>(*pEventData);
		reqCreateAvatar(data.roleType, data.name);
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("reqRemoveAvatar", "reqRemoveAvatar", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqRemoveAvatar& data = static_cast<const UKBEventData_reqRemoveAvatar&>(*pEventData);
		reqRemoveAvatar(data.avatarInfos.dbid);
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("selectAvatarGame", "selectAvatarGame", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_selectAvatarGame& data = static_cast<const UKBEventData_selectAvatarGame&>(*pEventData);
		selectAvatarGame(data.avatarInfos.dbid);
	});

	// 触发登陆成功事件
	UKBEventData_onLoginSuccessfully* pEventData = NewObject<UKBEventData_onLoginSuccessfully>();
	pEventData->entity_uuid = KBEngineApp::getSingleton().entity_uuid();
	pEventData->entity_id = id();
	KBENGINE_EVENT_FIRE("onLoginSuccessfully", pEventData);

	// 向服务端请求获得角色列表
	pBaseEntityCall->reqAvatarList();

}

void Account::onDestroy()
{
	// 注销注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void Account::onLastSelCharacterChanged(uint64 oldValue)
{

}

void Account::reqCreateAvatar(uint8 roleType, const FString& name)
{
	DEBUG_MSG("Account::reqCreateAvatar(): roleType=%d", roleType);
	pBaseEntityCall->reqCreateAvatar(roleType, name);
}

void Account::reqRemoveAvatar(uint64 dbid)
{
	DEBUG_MSG("Account::reqRemoveAvatar(): dbid=%lld", dbid);
	pBaseEntityCall->reqRemoveAvatarDBID(dbid);
}

void Account::selectAvatarGame(uint64 dbid)
{
	DEBUG_MSG("Account::selectAvatarGame(): name=%lld", dbid);
	pBaseEntityCall->selectAvatarGame(dbid);
}

void Account::onReqAvatarList(const AVATAR_INFOS_LIST& datas)
{
	UKBEventData_onReqAvatarList* pEventData = NewObject<UKBEventData_onReqAvatarList>();

	for (auto& characterInfoItem : datas.values)
	{
		FAVATAR_INFOS event_avatar;

		const AVATAR_INFOS& characterInfo_fixed_dict = characterInfoItem;
		AVATAR_INFOS infos;

		infos.name = characterInfo_fixed_dict.name;
		infos.dbid = characterInfo_fixed_dict.dbid;
		infos.level = characterInfo_fixed_dict.level;
		infos.roleType = characterInfo_fixed_dict.roleType;

		const AVATAR_DATA& data_fixed_dict = characterInfo_fixed_dict.data;

		infos.data.param1 = data_fixed_dict.param1;
		infos.data.param2 = data_fixed_dict.param2;

		characters.values.Add(infos);

		// fill eventData
		event_avatar.set(infos.dbid, infos.name, infos.roleType, infos.level, (lastSelCharacter == infos.dbid));
		pEventData->avatars.Add(event_avatar);
	}

	KBENGINE_EVENT_FIRE("onReqAvatarList", pEventData);
}

void Account::onCreateAvatarResult(uint8 retcode, const AVATAR_INFOS& info)
{
	UKBEventData_onCreateAvatarResult* pEventData = NewObject<UKBEventData_onCreateAvatarResult>();

	AVATAR_INFOS infos;

	infos.name = info.name;
	infos.dbid = info.dbid;
	infos.level = info.level;
	infos.roleType = info.roleType;

	const AVATAR_DATA& data_fixed_dict = info.data;

	infos.data.param1 = data_fixed_dict.param1;
	infos.data.param2 = data_fixed_dict.param2;

	if(retcode == 0)
		characters.values.Add(infos);

	// fill eventData
	pEventData->avatarInfos.set(infos.dbid, infos.name, infos.roleType, infos.level, (lastSelCharacter == infos.dbid));
	pEventData->errorCode = retcode;

	// Error codes given by Account::reqCreateAvatar on the server
	if (retcode > 0)
	{
		if (retcode == 3)
			pEventData->errorStr = TEXT("Limiting the number of characters!");
		else
			pEventData->errorStr = TEXT("Unknown error!");
	}

	KBENGINE_EVENT_FIRE("onCreateAvatarResult", pEventData);
}

void Account::onRemoveAvatar(uint64 dbid)
{
	DEBUG_MSG("Account::onRemoveAvatar(): dbid=%lld", dbid);

	int infosFind = -1;
	for (int32 index = 0; index != characters.values.Num(); ++index)
	{
		if(characters.values[index].dbid == dbid)
			infosFind = index;
	}

	if (infosFind < 0)
		return;

	AVATAR_INFOS infos = characters.values[infosFind];

	// ui event
	UKBEventData_onRemoveAvatar* pEventData = NewObject<UKBEventData_onRemoveAvatar>();
	pEventData->avatarInfos.set(infos.dbid, infos.name, infos.roleType, infos.level, (lastSelCharacter == infos.dbid));
	KBENGINE_EVENT_FIRE("onRemoveAvatar", pEventData);

	characters.values.RemoveAt(infosFind);
}

}