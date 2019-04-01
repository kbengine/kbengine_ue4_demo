#include "TestNoBase.h"
#include "Scripts/Avatar.h"
#include "Scripts/LogicEvents.h"

namespace KBEngine
{

TestNoBase::TestNoBase():
	TestNoBaseBase()
{
}

TestNoBase::~TestNoBase()
{
}

void TestNoBase::onAttached(Entity* pOwnerEntity)
{
	DEBUG_MSG("TestNoBase::onAttached: entity(%d)!", pOwnerEntity->id());
}

void TestNoBase::onDetached(Entity* pOwnerEntity)
{
	DEBUG_MSG("TestNoBase::onDetached: entity(%d)!", pOwnerEntity->id());
}

void TestNoBase::onOwnChanged(int32 oldValue) {
	DEBUG_MSG("TestNoBase::onOwnChanged: own(%d)!", oldValue);
}

void TestNoBase::onStateChanged(int32 oldValue) {
	DEBUG_MSG("TestNoBase::onOwnChanged: state(%d)!", oldValue);
}

void TestNoBase::helloCB(int32 arg1)
{
	DEBUG_MSG("TestNoBase::helloCB: arg1(%d)!", arg1);

	// 有可能还没有创建cell，所以pCellEntityCall可能为空
	if(pCellEntityCall)
		pCellEntityCall->hello(795);
}

}