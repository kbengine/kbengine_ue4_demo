#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "Avatar.h"

ENTITYDEF_CLASS_REGISTER(Avatar, GameObject)

Avatar::Avatar():
	GameObject()
{
}

Avatar::~Avatar()
{
}
