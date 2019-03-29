#include "Test.h"
#include "Scripts/Avatar.h"
#include "Scripts/LogicEvents.h"

namespace KBEngine
{

Test::Test():
	TestBase()
{
}

Test::~Test()
{
}

void Test::onAttached(Entity* pOwnerEntity)
{
	DEBUG_MSG("Test::onAttached: entity(%d)!", pOwnerEntity->id());
}

void Test::onDetached(Entity* pOwnerEntity)
{
	DEBUG_MSG("Test::onDetached: entity(%d)!", pOwnerEntity->id());
}

void Test::onOwnChanged(int32 oldValue) {
	DEBUG_MSG("Test::onOwnChanged: own(%d)!", oldValue);
}

void Test::onStateChanged(int32 oldValue) {
	DEBUG_MSG("Test::onOwnChanged: state(%d)!", oldValue);
}

void Test::helloCB(int32 arg1)
{
	DEBUG_MSG("Test::helloCB: arg1(%d)!", arg1);
	//((Avatar*)pOwner)->pCellEntityCall->component1->hello(795);
}

}