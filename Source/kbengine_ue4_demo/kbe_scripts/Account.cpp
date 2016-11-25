#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "Account.h"
#include "KBEngine.h"
#include "LogicEvents.h"

ENTITYDEF_CLASS_REGISTER(Account, GameObject)
ENTITYDEF_PROPERTY_REGISTER(Account, lastSelCharacter);
ENTITYDEF_METHOD_REGISTER(Account, onReqAvatarList);

Account::Account():
	GameObject(),
	characters(),
	lastSelCharacter(0)
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
		reqRemoveAvatar(data.dbid);
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("selectAvatarGame", "selectAvatarGame", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_selectAvatarGame& data = static_cast<const UKBEventData_selectAvatarGame&>(*pEventData);
		selectAvatarGame(data.dbid);
	});

	// 触发登陆成功事件
	UKBEventData_onLoginSuccessfully* pEventData = NewObject<UKBEventData_onLoginSuccessfully>();
	pEventData->entity_uuid = KBEngineApp::getSingleton().entity_uuid();
	pEventData->entity_id = id();
	KBENGINE_EVENT_FIRE("onLoginSuccessfully", pEventData);

	// 向服务端请求获得角色列表
	baseCall(TEXT("reqAvatarList"));
}

void Account::onDestroy()
{
	// 注销注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void Account::reqCreateAvatar(uint8 roleType, const FString& name)
{
	DEBUG_MSG("roleType=%d", roleType);
	// baseCall("reqCreateAvatar", roleType, name);
}

void Account::reqRemoveAvatar(const FString& name)
{
	DEBUG_MSG("name=%s", *name);
	// baseCall("reqRemoveAvatar", name);
}

void Account::reqRemoveAvatar(uint64 dbid)
{
	DEBUG_MSG("dbid=%lld", dbid);
	// baseCall("selectAvatarGame", dbid);
}

void Account::selectAvatarGame(uint64 dbid)
{
	DEBUG_MSG("name=%lld", dbid);
	//baseCall("selectAvatarGame", dbid);
}

void Account::onReqAvatarList(const KB_ARRAY& datas)
{
	UKBEventData_onReqAvatarList* pEventData = NewObject<UKBEventData_onReqAvatarList>();

	for (auto& item : datas)
	{
		const KB_FIXED_DICT& fixed_dict_values = item;
		KB_ARRAY values = fixed_dict_values[TEXT("values")];

		for (auto& characterInfoItem : values)
		{
			FAVATAR_INFOS event_avatar;

			const KB_FIXED_DICT& characterInfo_fixed_dict = characterInfoItem;
			AVATAR_INFOS infos;

			infos.name = characterInfo_fixed_dict[TEXT("name")].GetValue<FString>();
			infos.dbid = characterInfo_fixed_dict[TEXT("dbid")];
			infos.level = characterInfo_fixed_dict[TEXT("level")];
			infos.roleType = characterInfo_fixed_dict[TEXT("roleType")];

			const KB_FIXED_DICT& data_fixed_dict = characterInfo_fixed_dict[TEXT("data")];

			infos.data.param1 = data_fixed_dict[TEXT("param1")];
			infos.data.param2 = data_fixed_dict[TEXT("param2")].GetValue<TArray<uint8>>();

			characters.Add(infos.dbid, infos);

			// fill eventData
			event_avatar.name = infos.name;
			event_avatar.level = infos.level;
			event_avatar.roleType = infos.roleType;
			event_avatar.dbid = infos.dbid;
			pEventData->avatars.Add(event_avatar);
		}
	}

	KBENGINE_EVENT_FIRE("onReqAvatarList", pEventData);
}

void Account::onCreateAvatarResult(uint8 retcode, KB_FIXED_DICT& info)
{
	UKBEventData_onCreateAvatarResult* pEventData = NewObject<UKBEventData_onCreateAvatarResult>();

	const KB_FIXED_DICT& characterInfo_fixed_dict = info;
	AVATAR_INFOS infos;

	infos.name = characterInfo_fixed_dict[TEXT("name")].GetValue<FString>();
	infos.dbid = characterInfo_fixed_dict[TEXT("dbid")];
	infos.level = characterInfo_fixed_dict[TEXT("level")];
	infos.roleType = characterInfo_fixed_dict[TEXT("roleType")];

	const KB_FIXED_DICT& data_fixed_dict = characterInfo_fixed_dict[TEXT("data")];

	infos.data.param1 = data_fixed_dict[TEXT("param1")];
	infos.data.param2 = data_fixed_dict[TEXT("param2")].GetValue<TArray<uint8>>();

	characters.Add(infos.dbid, infos);

	// fill eventData
	pEventData->avatarInfos.name = infos.name;
	pEventData->avatarInfos.level = infos.level;
	pEventData->avatarInfos.roleType = infos.roleType;
	pEventData->avatarInfos.dbid = infos.dbid;
	pEventData->errorCode = retcode;
	pEventData->errorStr = KBEngineApp::getSingleton().serverErr(retcode);
	KBENGINE_EVENT_FIRE("onCreateAvatarResult", pEventData);
}

void Account::onRemoveAvatar(uint64 dbid)
{
	DEBUG_MSG("dbid=%lld", dbid);

	AVATAR_INFOS* infos = characters.Find(dbid);

	if (!infos)
		return;

	// ui event
	UKBEventData_onRemoveAvatar* pEventData = NewObject<UKBEventData_onRemoveAvatar>();
	pEventData->dbid = infos->dbid;
	KBENGINE_EVENT_FIRE("onRemoveAvatar", pEventData);
	characters.Remove(dbid);
}