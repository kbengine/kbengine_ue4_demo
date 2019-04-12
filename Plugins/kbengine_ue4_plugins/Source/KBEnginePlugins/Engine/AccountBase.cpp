#include "AccountBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"
#include "EntityComponent.h"

namespace KBEngine
{



void AccountBase::onComponentsEnterworld()
{
}

void AccountBase::onComponentsLeaveworld()
{
}

void AccountBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_AccountBase(id(), className());
}

void AccountBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_AccountBase(id(), className());
}

void AccountBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* AccountBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* AccountBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void AccountBase::onRemoteMethodCall(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("Account");
	uint16 methodUtype = 0;
	uint16 componentPropertyUType = 0;

	if (sm->usePropertyDescrAlias)
	{
		componentPropertyUType = stream.readUint8();
	}
	else
	{
		componentPropertyUType = stream.readUint16();
	}

	if (sm->useMethodDescrAlias)
	{
		methodUtype = stream.read<uint8>();
	}
	else
	{
		methodUtype = stream.read<uint16>();
	}

	if(componentPropertyUType > 0)
	{
		KBE_ASSERT(false);

		return;
	}

	Method* pMethod = sm->idmethods[methodUtype];

	switch(pMethod->methodUtype)
	{
		case 10005:
		{
			uint8 onCreateAvatarResult_arg1 = stream.readUint8();
			AVATAR_INFOS onCreateAvatarResult_arg2;
			((DATATYPE_AVATAR_INFOS*)pMethod->args[1])->createFromStreamEx(stream, onCreateAvatarResult_arg2);
			onCreateAvatarResult(onCreateAvatarResult_arg1, onCreateAvatarResult_arg2);
			break;
		}
		case 3:
		{
			uint64 onRemoveAvatar_arg1 = stream.readUint64();
			onRemoveAvatar(onRemoveAvatar_arg1);
			break;
		}
		case 10003:
		{
			AVATAR_INFOS_LIST onReqAvatarList_arg1;
			((DATATYPE_AVATAR_INFOS_LIST*)pMethod->args[0])->createFromStreamEx(stream, onReqAvatarList_arg1);
			onReqAvatarList(onReqAvatarList_arg1);
			break;
		}
		default:
			break;
	};
}

void AccountBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("Account");

	while(stream.length() > 0)
	{
		uint16 componentPropertyUType = 0;
		uint16 properUtype = 0;

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

		if(componentPropertyUType > 0)
		{
			KBE_ASSERT(false);

			return;
		}

		Property* pProp = sm->idpropertys[properUtype];

		switch(pProp->properUtype)
		{
			case 40001:
			{
				FVector oldval_direction = direction;
				direction = stream.readVector3();

				if(pProp->isBase())
				{
					if(inited())
						onDirectionChanged(oldval_direction);
				}
				else
				{
					if(inWorld())
						onDirectionChanged(oldval_direction);
				}

				break;
			}
			case 2:
			{
				uint64 oldval_lastSelCharacter = lastSelCharacter;
				lastSelCharacter = stream.readUint64();

				if(pProp->isBase())
				{
					if(inited())
						onLastSelCharacterChanged(oldval_lastSelCharacter);
				}
				else
				{
					if(inWorld())
						onLastSelCharacterChanged(oldval_lastSelCharacter);
				}

				break;
			}
			case 40000:
			{
				FVector oldval_position = position;
				position = stream.readVector3();

				if(pProp->isBase())
				{
					if(inited())
						onPositionChanged(oldval_position);
				}
				else
				{
					if(inWorld())
						onPositionChanged(oldval_position);
				}

				break;
			}
			case 40002:
			{
				stream.readUint32();
				break;
			}
			default:
				break;
		};
	}
}

void AccountBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["Account"];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	FVector oldval_direction = direction;
	Property* pProp_direction = pdatas[2];
	if(pProp_direction->isBase())
	{
		if(inited() && !inWorld())
			onDirectionChanged(oldval_direction);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_direction->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onDirectionChanged(oldval_direction);
			}
		}
	}

	uint64 oldval_lastSelCharacter = lastSelCharacter;
	Property* pProp_lastSelCharacter = pdatas[4];
	if(pProp_lastSelCharacter->isBase())
	{
		if(inited() && !inWorld())
			onLastSelCharacterChanged(oldval_lastSelCharacter);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_lastSelCharacter->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onLastSelCharacterChanged(oldval_lastSelCharacter);
			}
		}
	}

	FVector oldval_position = position;
	Property* pProp_position = pdatas[1];
	if(pProp_position->isBase())
	{
		if(inited() && !inWorld())
			onPositionChanged(oldval_position);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_position->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onPositionChanged(oldval_position);
			}
		}
	}

}

AccountBase::AccountBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	lastSelCharacter((uint64)FCString::Atoi64(TEXT("0")))
{
}

AccountBase::~AccountBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void AccountBase::attachComponents()
{
}

void AccountBase::detachComponents()
{
}

}