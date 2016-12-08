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

ENTITYDEF_CLASS_REGISTER(Avatar, GameObject, Combat, Motion, State, Flags, Spell, SkillBox, Teleport)

ENTITYDEF_DECLARE_GameObject(Avatar)
ENTITYDEF_DECLARE_Motion(Avatar)
ENTITYDEF_DECLARE_Teleport(Avatar)
ENTITYDEF_DECLARE_Combat(Avatar)
ENTITYDEF_DECLARE_State(Avatar)
ENTITYDEF_DECLARE_Flags(Avatar)



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

void Avatar::onDestroy()
{
	GameObject::onDestroy();
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
