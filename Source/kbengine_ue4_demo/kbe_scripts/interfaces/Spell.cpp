#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "Spell.h"

ENTITYDEF_CLASS_REGISTER(Spell)

Spell::Spell(Entity* entity) :
	self(entity)
{
}

Spell::~Spell()
{
}

