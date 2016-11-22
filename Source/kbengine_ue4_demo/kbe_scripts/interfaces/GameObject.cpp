#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "GameObject.h"

ENTITYDEF_CLASS_REGISTER(GameObject, Entity)

GameObject::GameObject():
	Entity(),
	name(),
	uid(0),
	utype(0),
	modelID(0),
	modelScale(0)
{
}

GameObject::~GameObject()
{
}
