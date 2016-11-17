#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "Account.h"

ENTITYDEF_CLASS_REGISTER(Account)
ENTITYDEF_METHOD_REGISTER(Account, set_spaceID)
ENTITYDEF_PROPERTY_REGISTER(Account, spaceID)

Account::Account():
	GameObject()
{
}

Account::~Account()
{
}
