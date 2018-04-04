#include "Test.h"
#include "Scripts/Avatar.h"
#include "Scripts/LogicEvents.h"

Test::Test():
	TestBase()
{
}

Test::~Test()
{
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
