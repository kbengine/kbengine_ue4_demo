#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "interfaces/NPCObject.h"
#include "Gate.h"

/*
	每个实体都需要将自己注册，格式为
	ENTITYDEF_CLASS_REGISTER(实体模块名，继承模块1，继承模块N，...)
*/
ENTITYDEF_CLASS_REGISTER(Gate, GameObject, NPCObject)

Gate::Gate():
	GameObject(),
	NPCObject(this)
{
}

Gate::~Gate()
{
}
