#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "LogicEvents.h"
#include "interfaces/GameObject.h"
#include "interfaces/Motion.h"
#include "interfaces/Combat.h"
#include "interfaces/State.h"
#include "interfaces/Flags.h"
#include "interfaces/Spell.h"
#include "interfaces/SkillBox.h"
#include "interfaces/Teleport.h"
#include "interfaces/AvatarLingGen.h"
#include "Avatar.h"

/*
	ÿ��ʵ�嶼��Ҫ���Լ�ע�ᣬ��ʽΪ
	ENTITYDEF_CLASS_REGISTER(ʵ��ģ�������̳�ģ��1���̳�ģ��N��...)
*/
ENTITYDEF_CLASS_REGISTER(Avatar, GameObject, Combat, Motion, State, Flags, Spell, SkillBox, Teleport, AvatarLingGen)

Avatar::Avatar():
	GameObject(),
	Combat(this),
	Motion(this),
	State(this),
	Flags(this),
	Spell(this),
	SkillBox(this),
	Teleport(this),
	AvatarLingGen(this)
{
}

Avatar::~Avatar()
{
}

void Avatar::__init__()
{
	// ע���¼�
	if (isPlayer())
	{
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("relive", "relive", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqRelive& data = static_cast<const UKBEventData_reqRelive&>(*pEventData);
			reqRelive(data.reliveType);
		});
	}
}


void Avatar::reqRelive(uint8 reliveType)
{
	DEBUG_MSG("Avatar::reqRelive(): reqRelive");
	cellCall("relive", reliveType);
}

void Avatar::onDestroy()
{
	GameObject::onDestroy();

	// ע��ע��������¼�
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void Avatar::onEnterWorld()
{
	GameObject::onEnterWorld();
}

void Avatar::onLeaveWorld()
{
	GameObject::onLeaveWorld();
}

void Avatar::onEnterSpace()
{
	GameObject::onEnterSpace();
}

void Avatar::onLeaveSpace()
{
	GameObject::onLeaveSpace();
}
