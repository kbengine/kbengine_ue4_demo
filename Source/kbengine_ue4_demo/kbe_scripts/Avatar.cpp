#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "Avatar.h"

ENTITYDEF_CLASS_REGISTER(Avatar, GameObject)
ENTITYDEF_PROPERTY_REGISTER(Avatar, level);
ENTITYDEF_PROPERTY_REGISTER(Avatar, own_val);

Avatar::Avatar():
	GameObject()
{
}

Avatar::~Avatar()
{
}
