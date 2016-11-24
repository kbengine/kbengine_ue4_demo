#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "Account.h"
#include "KBEngine.h"
#include "KBEvent.h"

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
}

void Account::reqRemoveAvatar(const FString& name)
{
	DEBUG_MSG("name=%s", *name);
}

void Account::reqRemoveAvatar(uint64 dbid)
{
	DEBUG_MSG("dbid=%lld", dbid);
}

void Account::onReqAvatarList(const KB_ARRAY& datas)
{
	for (auto& item : datas)
	{
		const KB_FIXED_DICT& fixed_dict_values = item;
		KB_ARRAY values = fixed_dict_values[TEXT("values")];

		for (auto& characterInfoItem : values)
		{
			const KB_FIXED_DICT& characterInfo_fixed_dict = characterInfoItem;
			AVATAR_INFOS infos;

			infos.name = characterInfo_fixed_dict[TEXT("name")].GetValue<FString>();
			infos.dbid = characterInfo_fixed_dict[TEXT("dbid")];
			infos.level = characterInfo_fixed_dict[TEXT("level")];
			infos.roleType = characterInfo_fixed_dict[TEXT("roleType")];

			const KB_FIXED_DICT& data_fixed_dict = characterInfo_fixed_dict[TEXT("data")];

			infos.data.param1 = data_fixed_dict[TEXT("param1")];
			infos.data.param2 = data_fixed_dict[TEXT("param2")].GetValue<TArray<uint8>>();

			characters.Add(infos.name, infos);
		}
	}
}