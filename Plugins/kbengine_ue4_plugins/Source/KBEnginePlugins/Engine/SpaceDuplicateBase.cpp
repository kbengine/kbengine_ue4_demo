#include "SpaceDuplicateBase.h"
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



void SpaceDuplicateBase::onComponentsEnterworld()
{
}

void SpaceDuplicateBase::onComponentsLeaveworld()
{
}

void SpaceDuplicateBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_SpaceDuplicateBase(id(), className());
}

void SpaceDuplicateBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_SpaceDuplicateBase(id(), className());
}

void SpaceDuplicateBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* SpaceDuplicateBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* SpaceDuplicateBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void SpaceDuplicateBase::onRemoteMethodCall(MemoryStream& stream)
{
}

void SpaceDuplicateBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("SpaceDuplicate");

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
			case 41006:
			{
				uint32 oldval_modelID = modelID;
				modelID = stream.readUint32();

				if(pProp->isBase())
				{
					if(inited())
						onModelIDChanged(oldval_modelID);
				}
				else
				{
					if(inWorld())
						onModelIDChanged(oldval_modelID);
				}

				break;
			}
			case 41007:
			{
				uint8 oldval_modelScale = modelScale;
				modelScale = stream.readUint8();

				if(pProp->isBase())
				{
					if(inited())
						onModelScaleChanged(oldval_modelScale);
				}
				else
				{
					if(inWorld())
						onModelScaleChanged(oldval_modelScale);
				}

				break;
			}
			case 41003:
			{
				FString oldval_name = name;
				name = stream.readUnicode();

				if(pProp->isBase())
				{
					if(inited())
						onNameChanged(oldval_name);
				}
				else
				{
					if(inWorld())
						onNameChanged(oldval_name);
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
			case 41004:
			{
				uint32 oldval_uid = uid;
				uid = stream.readUint32();

				if(pProp->isBase())
				{
					if(inited())
						onUidChanged(oldval_uid);
				}
				else
				{
					if(inWorld())
						onUidChanged(oldval_uid);
				}

				break;
			}
			case 41005:
			{
				uint32 oldval_utype = utype;
				utype = stream.readUint32();

				if(pProp->isBase())
				{
					if(inited())
						onUtypeChanged(oldval_utype);
				}
				else
				{
					if(inWorld())
						onUtypeChanged(oldval_utype);
				}

				break;
			}
			default:
				break;
		};
	}
}

void SpaceDuplicateBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["SpaceDuplicate"];
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

	uint32 oldval_modelID = modelID;
	Property* pProp_modelID = pdatas[4];
	if(pProp_modelID->isBase())
	{
		if(inited() && !inWorld())
			onModelIDChanged(oldval_modelID);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_modelID->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onModelIDChanged(oldval_modelID);
			}
		}
	}

	uint8 oldval_modelScale = modelScale;
	Property* pProp_modelScale = pdatas[5];
	if(pProp_modelScale->isBase())
	{
		if(inited() && !inWorld())
			onModelScaleChanged(oldval_modelScale);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_modelScale->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onModelScaleChanged(oldval_modelScale);
			}
		}
	}

	FString oldval_name = name;
	Property* pProp_name = pdatas[6];
	if(pProp_name->isBase())
	{
		if(inited() && !inWorld())
			onNameChanged(oldval_name);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_name->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onNameChanged(oldval_name);
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

	uint32 oldval_uid = uid;
	Property* pProp_uid = pdatas[7];
	if(pProp_uid->isBase())
	{
		if(inited() && !inWorld())
			onUidChanged(oldval_uid);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_uid->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onUidChanged(oldval_uid);
			}
		}
	}

	uint32 oldval_utype = utype;
	Property* pProp_utype = pdatas[8];
	if(pProp_utype->isBase())
	{
		if(inited() && !inWorld())
			onUtypeChanged(oldval_utype);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_utype->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onUtypeChanged(oldval_utype);
			}
		}
	}

}

SpaceDuplicateBase::SpaceDuplicateBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	modelID((uint32)FCString::Atoi64(TEXT("0"))),
	modelScale((uint8)FCString::Atoi64(TEXT("30"))),
	name(TEXT("")),
	uid((uint32)FCString::Atoi64(TEXT("0"))),
	utype((uint32)FCString::Atoi64(TEXT("0")))
{
}

SpaceDuplicateBase::~SpaceDuplicateBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void SpaceDuplicateBase::attachComponents()
{
}

void SpaceDuplicateBase::detachComponents()
{
}

}