#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "GameObject.h"

ENTITYDEF_CLASS_REGISTER(GameObject, Entity)
ENTITYDEF_PROPERTY_REGISTER(GameObject, name);
ENTITYDEF_PROPERTY_REGISTER(GameObject, uid);
ENTITYDEF_PROPERTY_REGISTER(GameObject, utype);
ENTITYDEF_PROPERTY_REGISTER(GameObject, modelID);
ENTITYDEF_PROPERTY_REGISTER(GameObject, modelScale);

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
