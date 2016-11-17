#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "Monster.h"

ENTITYDEF_CLASS_REGISTER(Monster)

Monster::Monster():
	GameObject()
{
}

Monster::~Monster()
{
}
