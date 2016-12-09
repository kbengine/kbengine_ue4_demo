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
#include "Avatar.h"

/*
	每个实体都需要将自己注册，格式为
	ENTITYDEF_CLASS_REGISTER(实体模块名，继承模块1，继承模块N，...)
*/
ENTITYDEF_CLASS_REGISTER(Avatar, GameObject, Combat, Motion, State, Flags, Spell, SkillBox, Teleport)

Avatar::Avatar():
	GameObject(),
	Combat(this),
	Motion(this),
	State(this),
	Flags(this),
	Spell(this),
	SkillBox(this),
	Teleport(this)
{
}

Avatar::~Avatar()
{
}

void Avatar::__init__()
{
	// 注册事件
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
	DEBUG_MSG("reqRelive");
	cellCall("relive", reliveType);
}

void Avatar::onDestroy()
{
	GameObject::onDestroy();

	// 注销注册的所有事件
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
