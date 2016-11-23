#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "GameObject.h"

ENTITYDEF_CLASS_REGISTER(GameObject, Entity)

// 由于与底层某些名称冲突，所以这里使用了一个别名防止冲突
ENTITYDEF_PROPERTY_ALIAS_REGISTER(GameObject, name, name_);

ENTITYDEF_PROPERTY_REGISTER(GameObject, uid);
ENTITYDEF_PROPERTY_REGISTER(GameObject, utype);
ENTITYDEF_PROPERTY_REGISTER(GameObject, modelID);
ENTITYDEF_PROPERTY_REGISTER(GameObject, modelScale);

GameObject::GameObject():
	Entity(),
	name_(),
	uid(0),
	utype(0),
	modelID(0),
	modelScale(0)
{
}

GameObject::~GameObject()
{
}
