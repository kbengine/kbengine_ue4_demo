#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "Gate.h"

ENTITYDEF_CLASS_REGISTER(Gate)

Gate::Gate():
	GameObject()
{
}

Gate::~Gate()
{
}
