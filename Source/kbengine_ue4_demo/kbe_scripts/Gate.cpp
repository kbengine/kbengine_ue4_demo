#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "interfaces/NPCObject.h"
#include "Gate.h"

ENTITYDEF_CLASS_REGISTER(Gate, GameObject, NPCObject)

ENTITYDEF_DECLARE_GameObject(Gate)
ENTITYDEF_DECLARE_NPCObject(Gate)


Gate::Gate():
	GameObject(),
	NPCObject(this)
{
}

Gate::~Gate()
{
}
