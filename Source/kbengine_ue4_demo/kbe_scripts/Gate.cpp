#include "Gate.h"
#include "kbengine_ue4_demo.h"
#include "Entity.h"

/*
	每个实体都需要将自己注册，格式为
	ENTITYDEF_CLASS_REGISTER(实体模块名，继承模块1，继承模块N，...)

	当实体类没有继承任何def中的类时使用该宏, 如这种实体: class Monster : public Entity
	ENTITYDEF_CLASS_NO_DEFPARENT_REGISTER
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
