#include "AvatarBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"
#include "EntityComponent.h"

#include "Scripts/Components/Test.h"

#include "Scripts/Components/TestNoBase.h"

namespace KBEngine
{



void AvatarBase::onComponentsEnterworld()
{
	component1->onEnterworld();
	component2->onEnterworld();
	component3->onEnterworld();
}

void AvatarBase::onComponentsLeaveworld()
{
	component1->onLeaveworld();
	component2->onLeaveworld();
	component3->onLeaveworld();
}

void AvatarBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_AvatarBase(id(), className());
	component1->onGetBase();
	component2->onGetBase();
	component3->onGetBase();
}

void AvatarBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_AvatarBase(id(), className());
	component1->onGetCell();
	component2->onGetCell();
	component3->onGetCell();
}

void AvatarBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
	component1->onLoseCell();
	component2->onLoseCell();
	component3->onLoseCell();
}

EntityCall* AvatarBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* AvatarBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void AvatarBase::onRemoteMethodCall(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("Avatar");
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
		Property* pComponentPropertyDescription = sm->idpropertys[componentPropertyUType];

		switch(pComponentPropertyDescription->properUtype)
		{
			case 16:
				component1->onRemoteMethodCall(methodUtype, stream);
				break;
			case 21:
				component2->onRemoteMethodCall(methodUtype, stream);
				break;
			case 22:
				component3->onRemoteMethodCall(methodUtype, stream);
				break;
		}

		return;
	}

	Method* pMethod = sm->idmethods[methodUtype];

	switch(pMethod->methodUtype)
	{
		case 10101:
		{
			uint8 dialog_addOption_arg1 = stream.readUint8();
			uint32 dialog_addOption_arg2 = stream.readUint32();
			FString dialog_addOption_arg3 = stream.readUnicode();
			int32 dialog_addOption_arg4 = stream.readInt32();
			dialog_addOption(dialog_addOption_arg1, dialog_addOption_arg2, dialog_addOption_arg3, dialog_addOption_arg4);
			break;
		}
		case 10104:
		{
			dialog_close();
			break;
		}
		case 10102:
		{
			FString dialog_setText_arg1 = stream.readUnicode();
			uint8 dialog_setText_arg2 = stream.readUint8();
			uint32 dialog_setText_arg3 = stream.readUint32();
			FString dialog_setText_arg4 = stream.readUnicode();
			dialog_setText(dialog_setText_arg1, dialog_setText_arg2, dialog_setText_arg3, dialog_setText_arg4);
			break;
		}
		case 12:
		{
			int32 onAddSkill_arg1 = stream.readInt32();
			onAddSkill(onAddSkill_arg1);
			break;
		}
		case 7:
		{
			onJump();
			break;
		}
		case 13:
		{
			int32 onRemoveSkill_arg1 = stream.readInt32();
			onRemoveSkill(onRemoveSkill_arg1);
			break;
		}
		case 16:
		{
			int32 recvDamage_arg1 = stream.readInt32();
			int32 recvDamage_arg2 = stream.readInt32();
			int32 recvDamage_arg3 = stream.readInt32();
			int32 recvDamage_arg4 = stream.readInt32();
			recvDamage(recvDamage_arg1, recvDamage_arg2, recvDamage_arg3, recvDamage_arg4);
			break;
		}
		default:
			break;
	};
}

void AvatarBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("Avatar");

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
			Property* pComponentPropertyDescription = sm->idpropertys[componentPropertyUType];

			switch(pComponentPropertyDescription->properUtype)
			{
				case 16:
					component1->onUpdatePropertys(properUtype, stream, -1);
					break;
				case 21:
					component2->onUpdatePropertys(properUtype, stream, -1);
					break;
				case 22:
					component3->onUpdatePropertys(properUtype, stream, -1);
					break;
			}

			return;
		}

		Property* pProp = sm->idpropertys[properUtype];

		switch(pProp->properUtype)
		{
			case 47001:
			{
				int32 oldval_HP = HP;
				HP = stream.readInt32();

				if(pProp->isBase())
				{
					if(inited())
						onHPChanged(oldval_HP);
				}
				else
				{
					if(inWorld())
						onHPChanged(oldval_HP);
				}

				break;
			}
			case 47002:
			{
				int32 oldval_HP_Max = HP_Max;
				HP_Max = stream.readInt32();

				if(pProp->isBase())
				{
					if(inited())
						onHP_MaxChanged(oldval_HP_Max);
				}
				else
				{
					if(inWorld())
						onHP_MaxChanged(oldval_HP_Max);
				}

				break;
			}
			case 47003:
			{
				int32 oldval_MP = MP;
				MP = stream.readInt32();

				if(pProp->isBase())
				{
					if(inited())
						onMPChanged(oldval_MP);
				}
				else
				{
					if(inWorld())
						onMPChanged(oldval_MP);
				}

				break;
			}
			case 47004:
			{
				int32 oldval_MP_Max = MP_Max;
				MP_Max = stream.readInt32();

				if(pProp->isBase())
				{
					if(inited())
						onMP_MaxChanged(oldval_MP_Max);
				}
				else
				{
					if(inWorld())
						onMP_MaxChanged(oldval_MP_Max);
				}

				break;
			}
			case 16:
				component1->createFromStream(stream);
				break;
			case 21:
				component2->createFromStream(stream);
				break;
			case 22:
				component3->createFromStream(stream);
				break;
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
			case 47005:
			{
				int32 oldval_forbids = forbids;
				forbids = stream.readInt32();

				if(pProp->isBase())
				{
					if(inited())
						onForbidsChanged(oldval_forbids);
				}
				else
				{
					if(inWorld())
						onForbidsChanged(oldval_forbids);
				}

				break;
			}
			case 41002:
			{
				uint16 oldval_level = level;
				level = stream.readUint16();

				if(pProp->isBase())
				{
					if(inited())
						onLevelChanged(oldval_level);
				}
				else
				{
					if(inWorld())
						onLevelChanged(oldval_level);
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
			case 11:
			{
				uint8 oldval_moveSpeed = moveSpeed;
				moveSpeed = stream.readUint8();

				if(pProp->isBase())
				{
					if(inited())
						onMoveSpeedChanged(oldval_moveSpeed);
				}
				else
				{
					if(inWorld())
						onMoveSpeedChanged(oldval_moveSpeed);
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
			case 6:
			{
				uint16 oldval_own_val = own_val;
				own_val = stream.readUint16();

				if(pProp->isBase())
				{
					if(inited())
						onOwn_valChanged(oldval_own_val);
				}
				else
				{
					if(inWorld())
						onOwn_valChanged(oldval_own_val);
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
			case 41001:
			{
				uint32 oldval_spaceUType = spaceUType;
				spaceUType = stream.readUint32();

				if(pProp->isBase())
				{
					if(inited())
						onSpaceUTypeChanged(oldval_spaceUType);
				}
				else
				{
					if(inWorld())
						onSpaceUTypeChanged(oldval_spaceUType);
				}

				break;
			}
			case 47006:
			{
				int8 oldval_state = state;
				state = stream.readInt8();

				if(pProp->isBase())
				{
					if(inited())
						onStateChanged(oldval_state);
				}
				else
				{
					if(inWorld())
						onStateChanged(oldval_state);
				}

				break;
			}
			case 47007:
			{
				uint8 oldval_subState = subState;
				subState = stream.readUint8();

				if(pProp->isBase())
				{
					if(inited())
						onSubStateChanged(oldval_subState);
				}
				else
				{
					if(inWorld())
						onSubStateChanged(oldval_subState);
				}

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

void AvatarBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["Avatar"];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	int32 oldval_HP = HP;
	Property* pProp_HP = pdatas[4];
	if(pProp_HP->isBase())
	{
		if(inited() && !inWorld())
			onHPChanged(oldval_HP);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_HP->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onHPChanged(oldval_HP);
			}
		}
	}

	int32 oldval_HP_Max = HP_Max;
	Property* pProp_HP_Max = pdatas[5];
	if(pProp_HP_Max->isBase())
	{
		if(inited() && !inWorld())
			onHP_MaxChanged(oldval_HP_Max);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_HP_Max->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onHP_MaxChanged(oldval_HP_Max);
			}
		}
	}

	int32 oldval_MP = MP;
	Property* pProp_MP = pdatas[6];
	if(pProp_MP->isBase())
	{
		if(inited() && !inWorld())
			onMPChanged(oldval_MP);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_MP->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onMPChanged(oldval_MP);
			}
		}
	}

	int32 oldval_MP_Max = MP_Max;
	Property* pProp_MP_Max = pdatas[7];
	if(pProp_MP_Max->isBase())
	{
		if(inited() && !inWorld())
			onMP_MaxChanged(oldval_MP_Max);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_MP_Max->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onMP_MaxChanged(oldval_MP_Max);
			}
		}
	}

	component1->callPropertysSetMethods();

	component2->callPropertysSetMethods();

	component3->callPropertysSetMethods();

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

	int32 oldval_forbids = forbids;
	Property* pProp_forbids = pdatas[11];
	if(pProp_forbids->isBase())
	{
		if(inited() && !inWorld())
			onForbidsChanged(oldval_forbids);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_forbids->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onForbidsChanged(oldval_forbids);
			}
		}
	}

	uint16 oldval_level = level;
	Property* pProp_level = pdatas[12];
	if(pProp_level->isBase())
	{
		if(inited() && !inWorld())
			onLevelChanged(oldval_level);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_level->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onLevelChanged(oldval_level);
			}
		}
	}

	uint32 oldval_modelID = modelID;
	Property* pProp_modelID = pdatas[13];
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
	Property* pProp_modelScale = pdatas[14];
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

	uint8 oldval_moveSpeed = moveSpeed;
	Property* pProp_moveSpeed = pdatas[15];
	if(pProp_moveSpeed->isBase())
	{
		if(inited() && !inWorld())
			onMoveSpeedChanged(oldval_moveSpeed);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_moveSpeed->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onMoveSpeedChanged(oldval_moveSpeed);
			}
		}
	}

	FString oldval_name = name;
	Property* pProp_name = pdatas[16];
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

	uint16 oldval_own_val = own_val;
	Property* pProp_own_val = pdatas[17];
	if(pProp_own_val->isBase())
	{
		if(inited() && !inWorld())
			onOwn_valChanged(oldval_own_val);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_own_val->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onOwn_valChanged(oldval_own_val);
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

	uint32 oldval_spaceUType = spaceUType;
	Property* pProp_spaceUType = pdatas[18];
	if(pProp_spaceUType->isBase())
	{
		if(inited() && !inWorld())
			onSpaceUTypeChanged(oldval_spaceUType);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_spaceUType->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onSpaceUTypeChanged(oldval_spaceUType);
			}
		}
	}

	int8 oldval_state = state;
	Property* pProp_state = pdatas[19];
	if(pProp_state->isBase())
	{
		if(inited() && !inWorld())
			onStateChanged(oldval_state);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_state->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onStateChanged(oldval_state);
			}
		}
	}

	uint8 oldval_subState = subState;
	Property* pProp_subState = pdatas[20];
	if(pProp_subState->isBase())
	{
		if(inited() && !inWorld())
			onSubStateChanged(oldval_subState);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_subState->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onSubStateChanged(oldval_subState);
			}
		}
	}

	uint32 oldval_uid = uid;
	Property* pProp_uid = pdatas[21];
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
	Property* pProp_utype = pdatas[22];
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

AvatarBase::AvatarBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	HP((int32)FCString::Atoi64(TEXT("0"))),
	HP_Max((int32)FCString::Atoi64(TEXT("0"))),
	MP((int32)FCString::Atoi64(TEXT("0"))),
	MP_Max((int32)FCString::Atoi64(TEXT("0"))),
	component1(new Test()),
	component2(new Test()),
	component3(new TestNoBase()),
	forbids((int32)FCString::Atoi64(TEXT("0"))),
	level((uint16)FCString::Atoi64(TEXT("0"))),
	modelID((uint32)FCString::Atoi64(TEXT("0"))),
	modelScale((uint8)FCString::Atoi64(TEXT("30"))),
	moveSpeed((uint8)FCString::Atoi64(TEXT("50"))),
	name(TEXT("")),
	own_val((uint16)FCString::Atoi64(TEXT("0"))),
	spaceUType((uint32)FCString::Atoi64(TEXT("0"))),
	state((int8)FCString::Atoi64(TEXT("0"))),
	subState((uint8)FCString::Atoi64(TEXT("0"))),
	uid((uint32)FCString::Atoi64(TEXT("0"))),
	utype((uint32)FCString::Atoi64(TEXT("0")))
{
	component1->pOwner = this;
	component1->ownerID = id_;
	component1->entityComponentPropertyID = 16;
	component1->name_ = "Test";

	component2->pOwner = this;
	component2->ownerID = id_;
	component2->entityComponentPropertyID = 21;
	component2->name_ = "Test";

	component3->pOwner = this;
	component3->ownerID = id_;
	component3->entityComponentPropertyID = 22;
	component3->name_ = "TestNoBase";

}

AvatarBase::~AvatarBase()
{
	if(component1)
		delete component1;

	if(component2)
		delete component2;

	if(component3)
		delete component3;

	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void AvatarBase::attachComponents()
{
	component1->onAttached(this);
	component2->onAttached(this);
	component3->onAttached(this);
}

void AvatarBase::detachComponents()
{
	component1->onDetached(this);
	component2->onDetached(this);
	component3->onDetached(this);
}

TArray<EntityComponent*> AvatarBase::getComponents(FString componentName, bool all)
{
	TArray<EntityComponent*> founds;

	if(component1->name_ == componentName)
	{
		founds.Add(component1);
		if(!all)
			return founds;
	}

	if(component2->name_ == componentName)
	{
		founds.Add(component2);
		if(!all)
			return founds;
	}

	if(component3->name_ == componentName)
	{
		founds.Add(component3);
		if(!all)
			return founds;
	}

	return founds;
}

}