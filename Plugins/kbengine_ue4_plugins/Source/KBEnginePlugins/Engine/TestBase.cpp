#include "TestBase.h"
#include "KBVar.h"
#include "Entity.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"

namespace KBEngine
{



void TestBase::createFromStream(MemoryStream& stream)
{
	EntityComponent::createFromStream(stream);
}

void TestBase::onGetBase()
{
	ownerID = pOwner->id();

	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_TestBase(entityComponentPropertyID, ownerID);
}

void TestBase::onGetCell()
{
	ownerID = pOwner->id();

	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_TestBase(entityComponentPropertyID, ownerID);
}

void TestBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}


ScriptModule* TestBase::getScriptModule()
{
	return *EntityDef::moduledefs.Find("Test");
}

void TestBase::onRemoteMethodCall(uint16 methodUtype, MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("Test");
	Method* pMethod = sm->idmethods[methodUtype];

	switch(pMethod->methodUtype)
	{
		case 28:
		{
			int32 helloCB_arg1 = stream.readInt32();
			helloCB(helloCB_arg1);
			break;
		}
		default:
			break;
	};
}

void TestBase::onUpdatePropertys(uint16 propUtype, MemoryStream& stream, int maxCount)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("Test");

	while(stream.length() > 0 && maxCount-- != 0)
	{
		uint16 componentPropertyUType = 0;
		uint16 properUtype = propUtype;

		if (properUtype == 0)
		{
			if (sm->usePropertyDescrAlias)
			{
				componentPropertyUType = stream.readUint8();
				properUtype = stream.read<uint8>();
			}
			else
			{
				componentPropertyUType = stream.readUint16();
				properUtype = stream.read<uint16>();
			}
		}

		Property* pProp = sm->idpropertys[properUtype];

		switch(pProp->properUtype)
		{
			case 18:
			{
				int32 oldval_own = own;
				own = stream.readInt32();

				if(pProp->isBase())
				{
					if(pOwner->inited())
						onOwnChanged(oldval_own);
				}
				else
				{
					if(pOwner->inWorld())
						onOwnChanged(oldval_own);
				}

				break;
			}
			case 17:
			{
				int32 oldval_state = state;
				state = stream.readInt32();

				if(pProp->isBase())
				{
					if(pOwner->inited())
						onStateChanged(oldval_state);
				}
				else
				{
					if(pOwner->inWorld())
						onStateChanged(oldval_state);
				}

				break;
			}
			default:
				break;
		};
	}
}

void TestBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["Test"];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	int32 oldval_own = own;
	Property* pProp_own = pdatas[4];
	if(pProp_own->isBase())
	{
		if(pOwner->inited() && !pOwner->inWorld())
			onOwnChanged(oldval_own);
	}
	else
	{
		if(pOwner->inWorld())
		{
			if(pProp_own->isOwnerOnly() && !pOwner->isPlayer())
			{
			}
			else
			{
				onOwnChanged(oldval_own);
			}
		}
	}

	int32 oldval_state = state;
	Property* pProp_state = pdatas[5];
	if(pProp_state->isBase())
	{
		if(pOwner->inited() && !pOwner->inWorld())
			onStateChanged(oldval_state);
	}
	else
	{
		if(pOwner->inWorld())
		{
			if(pProp_state->isOwnerOnly() && !pOwner->isPlayer())
			{
			}
			else
			{
				onStateChanged(oldval_state);
			}
		}
	}

}

TestBase::TestBase():
	EntityComponent(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	own((int32)FCString::Atoi64(TEXT("1001"))),
	state((int32)FCString::Atoi64(TEXT("100")))
{
}

TestBase::~TestBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

}