#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "interfaces/NPCObject.h"
#include "interfaces/Motion.h"
#include "interfaces/Combat.h"
#include "interfaces/State.h"
#include "interfaces/Flags.h"
#include "interfaces/Spell.h"
#include "Monster.h"

ENTITYDEF_CLASS_REGISTER(Monster, GameObject, NPCObject, Combat, Motion, State, Flags, Spell)

ENTITYDEF_DECLARE_GameObject(Monster)
ENTITYDEF_DECLARE_Combat(Monster)
ENTITYDEF_DECLARE_Motion(Monster)
ENTITYDEF_DECLARE_State(Monster)
ENTITYDEF_DECLARE_Flags(Monster)
ENTITYDEF_DECLARE_NPCObject(Monster)


Monster::Monster():
	GameObject(),
	NPCObject(this),
	Combat(this),
	Motion(this),
	State(this),
	Flags(this),
	Spell(this)
{
}

Monster::~Monster()
{
}
