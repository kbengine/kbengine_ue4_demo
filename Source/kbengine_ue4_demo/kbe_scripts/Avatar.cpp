#include "kbengine_ue4_demo.h"
#include "Entity.h"
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

ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Avatar, position)
ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Avatar, direction)
ENTITYDEF_PROPERTY_REGISTER(Avatar, spaceID)

// 由于与底层某些名称冲突，所以这里使用了一个别名防止冲突
ENTITYDEF_PROPERTY_ALIAS_REGISTER(Avatar, name, name_);

ENTITYDEF_PROPERTY_REGISTER(Avatar, uid);
ENTITYDEF_PROPERTY_REGISTER(Avatar, utype);
ENTITYDEF_PROPERTY_REGISTER(Avatar, modelID);
ENTITYDEF_PROPERTY_REGISTER(Avatar, modelScale);

ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Avatar, flags);

ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Avatar, state);
ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Avatar, subState);
ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Avatar, forbids);

ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Avatar, moveSpeed);

ENTITYDEF_PROPERTY_REGISTER(Avatar, level);
ENTITYDEF_PROPERTY_REGISTER(Avatar, own_val);


ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Avatar, HP);
ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Avatar, HP_Max);
ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Avatar, MP);
ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Avatar, MP_Max);

ENTITYDEF_PROPERTY_REGISTER(Avatar, spaceUType);

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
