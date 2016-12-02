#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "GameObject.h"

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
