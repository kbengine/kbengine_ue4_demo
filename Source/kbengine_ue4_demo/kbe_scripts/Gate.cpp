#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "interfaces/NPCObject.h"
#include "Gate.h"

ENTITYDEF_CLASS_REGISTER(Gate, GameObject, NPCObject)

Gate::Gate():
	GameObject(),
	NPCObject(this)
{
}

Gate::~Gate()
{
}
