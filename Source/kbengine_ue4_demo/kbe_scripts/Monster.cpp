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

/*
	每个实体都需要将自己注册，格式为
	ENTITYDEF_CLASS_REGISTER(实体模块名，继承模块1，继承模块N，...)
*/
ENTITYDEF_CLASS_REGISTER(Monster, GameObject, NPCObject, Combat, Motion, State, Flags, Spell)

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
