#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "interfaces/Motion.h"
#include "interfaces/Combat.h"
#include "interfaces/State.h"
#include "interfaces/Flags.h"
#include "interfaces/Spell.h"
#include "interfaces/SkillBox.h"
#include "Avatar.h"

ENTITYDEF_CLASS_REGISTER(Avatar, GameObject, Combat, Motion, State, Flags, Spell, SkillBox)
ENTITYDEF_PROPERTY_REGISTER(Avatar, level);
ENTITYDEF_PROPERTY_REGISTER(Avatar, own_val);

Avatar::Avatar():
	GameObject(),
	Combat(this),
	Motion(this),
	State(this),
	Flags(this),
	Spell(this),
	SkillBox(this)
{
}

Avatar::~Avatar()
{
}
