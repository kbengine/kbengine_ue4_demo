#include "EntityDef.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "KBVar.h"
#include "Entity.h"

#include "Scripts/Account.h"
#include "Scripts/Avatar.h"
#include "Scripts/Components/Test.h"
#include "Scripts/Components/TestNoBase.h"
#include "Scripts/Monster.h"
#include "Scripts/NPC.h"
#include "Scripts/Gate.h"

namespace KBEngine
{

TMap<FString, uint16> EntityDef::datatype2id;
TMap<FString, DATATYPE_BASE*> EntityDef::datatypes;
TMap<uint16, DATATYPE_BASE*> EntityDef::id2datatypes;
TMap<FString, int32> EntityDef::entityclass;
TMap<FString, ScriptModule*> EntityDef::moduledefs;
TMap<uint16, ScriptModule*> EntityDef::idmoduledefs;

bool EntityDef::initialize()
{
	initDataTypes();
	initDefTypes();
	initScriptModules();
	return true;
}

bool EntityDef::reset()
{
	clear();
	return initialize();
}

void EntityDef::clear()
{
	TArray<DATATYPE_BASE*> deleted_datatypes;
	for (auto& item : EntityDef::datatypes)
	{
		int32 idx = deleted_datatypes.Find(item.Value);
		if (idx != INDEX_NONE)
			continue;

		deleted_datatypes.Add(item.Value);
		delete item.Value;
	}

	for (auto& item : EntityDef::moduledefs)
		delete item.Value;

	datatype2id.Empty();
	datatypes.Empty();
	id2datatypes.Empty();
	entityclass.Empty();
	moduledefs.Empty();
	idmoduledefs.Empty();
}

void EntityDef::initDataTypes()
{
	datatypes.Add(TEXT("UINT8"), new DATATYPE_UINT8());
	datatypes.Add(TEXT("UINT16"), new DATATYPE_UINT16());
	datatypes.Add(TEXT("UINT32"), new DATATYPE_UINT32());
	datatypes.Add(TEXT("UINT64"), new DATATYPE_UINT64());

	datatypes.Add(TEXT("INT8"), new DATATYPE_INT8());
	datatypes.Add(TEXT("INT16"), new DATATYPE_INT16());
	datatypes.Add(TEXT("INT32"), new DATATYPE_INT32());
	datatypes.Add(TEXT("INT64"), new DATATYPE_INT64());

	datatypes.Add(TEXT("FLOAT"), new DATATYPE_FLOAT());
	datatypes.Add(TEXT("DOUBLE"), new DATATYPE_DOUBLE());

	datatypes.Add(TEXT("STRING"), new DATATYPE_STRING());
	datatypes.Add(TEXT("VECTOR2"), new DATATYPE_VECTOR2());

	datatypes.Add(TEXT("VECTOR3"), new DATATYPE_VECTOR3());

	datatypes.Add(TEXT("VECTOR4"), new DATATYPE_VECTOR4());
	datatypes.Add(TEXT("PYTHON"), new DATATYPE_PYTHON());

	datatypes.Add(TEXT("UNICODE"), new DATATYPE_UNICODE());
	datatypes.Add(TEXT("ENTITYCALL"), new DATATYPE_ENTITYCALL());

	datatypes.Add(TEXT("BLOB"), new DATATYPE_BLOB());
}

Entity* EntityDef::createEntity(int utype)
{
	Entity* pEntity = NULL;

	switch(utype)
	{
		case 1:
			pEntity = new Account();
			break;
		case 2:
			pEntity = new Avatar();
			break;
		case 5:
			pEntity = new Monster();
			break;
		case 6:
			pEntity = new NPC();
			break;
		case 7:
			pEntity = new Gate();
			break;
		default:
			SCREEN_ERROR_MSG("EntityDef::createEntity() : entity(%d) not found!", utype);
			break;
	};

	return pEntity;
}

void EntityDef::initScriptModules()
{
	ScriptModule* pAccountModule = new ScriptModule("Account", 1);
	EntityDef::moduledefs.Add(TEXT("Account"), pAccountModule);
	EntityDef::idmoduledefs.Add(1, pAccountModule);

	Property* pAccount_position = new Property();
	pAccount_position->name = TEXT("position");
	pAccount_position->properUtype = 40000;
	pAccount_position->properFlags = 4;
	pAccount_position->aliasID = 1;
	KBVar* pAccount_position_defval = new KBVar(FVector());
	pAccount_position->pDefaultVal = pAccount_position_defval;
	pAccountModule->propertys.Add(TEXT("position"), pAccount_position); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_position->aliasID, pAccount_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(position / 40000).");

	Property* pAccount_direction = new Property();
	pAccount_direction->name = TEXT("direction");
	pAccount_direction->properUtype = 40001;
	pAccount_direction->properFlags = 4;
	pAccount_direction->aliasID = 2;
	KBVar* pAccount_direction_defval = new KBVar(FVector());
	pAccount_direction->pDefaultVal = pAccount_direction_defval;
	pAccountModule->propertys.Add(TEXT("direction"), pAccount_direction); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_direction->aliasID, pAccount_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(direction / 40001).");

	Property* pAccount_spaceID = new Property();
	pAccount_spaceID->name = TEXT("spaceID");
	pAccount_spaceID->properUtype = 40002;
	pAccount_spaceID->properFlags = 16;
	pAccount_spaceID->aliasID = 3;
	KBVar* pAccount_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pAccount_spaceID->pDefaultVal = pAccount_spaceID_defval;
	pAccountModule->propertys.Add(TEXT("spaceID"), pAccount_spaceID); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_spaceID->aliasID, pAccount_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(spaceID / 40002).");

	Property* pAccount_lastSelCharacter = new Property();
	pAccount_lastSelCharacter->name = TEXT("lastSelCharacter");
	pAccount_lastSelCharacter->properUtype = 2;
	pAccount_lastSelCharacter->properFlags = 32;
	pAccount_lastSelCharacter->aliasID = 4;
	KBVar* pAccount_lastSelCharacter_defval = new KBVar((uint64)FCString::Atoi64(TEXT("0")));
	pAccount_lastSelCharacter->pDefaultVal = pAccount_lastSelCharacter_defval;
	pAccountModule->propertys.Add(TEXT("lastSelCharacter"), pAccount_lastSelCharacter); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_lastSelCharacter->aliasID, pAccount_lastSelCharacter);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(lastSelCharacter / 2).");

	TArray<DATATYPE_BASE*> Account_onCreateAvatarResult_args;
	Account_onCreateAvatarResult_args.Add(EntityDef::id2datatypes[2]);
	Account_onCreateAvatarResult_args.Add(EntityDef::id2datatypes[25]);

	Method* pAccount_onCreateAvatarResult = new Method();
	pAccount_onCreateAvatarResult->name = TEXT("onCreateAvatarResult");
	pAccount_onCreateAvatarResult->methodUtype = 10005;
	pAccount_onCreateAvatarResult->aliasID = 1;
	pAccount_onCreateAvatarResult->args = Account_onCreateAvatarResult_args;

	pAccountModule->methods.Add(TEXT("onCreateAvatarResult"), pAccount_onCreateAvatarResult); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_onCreateAvatarResult->aliasID, pAccount_onCreateAvatarResult);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(onCreateAvatarResult / 10005).");

	TArray<DATATYPE_BASE*> Account_onRemoveAvatar_args;
	Account_onRemoveAvatar_args.Add(EntityDef::id2datatypes[5]);

	Method* pAccount_onRemoveAvatar = new Method();
	pAccount_onRemoveAvatar->name = TEXT("onRemoveAvatar");
	pAccount_onRemoveAvatar->methodUtype = 3;
	pAccount_onRemoveAvatar->aliasID = 2;
	pAccount_onRemoveAvatar->args = Account_onRemoveAvatar_args;

	pAccountModule->methods.Add(TEXT("onRemoveAvatar"), pAccount_onRemoveAvatar); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_onRemoveAvatar->aliasID, pAccount_onRemoveAvatar);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(onRemoveAvatar / 3).");

	TArray<DATATYPE_BASE*> Account_onReqAvatarList_args;
	Account_onReqAvatarList_args.Add(EntityDef::id2datatypes[26]);

	Method* pAccount_onReqAvatarList = new Method();
	pAccount_onReqAvatarList->name = TEXT("onReqAvatarList");
	pAccount_onReqAvatarList->methodUtype = 10003;
	pAccount_onReqAvatarList->aliasID = 3;
	pAccount_onReqAvatarList->args = Account_onReqAvatarList_args;

	pAccountModule->methods.Add(TEXT("onReqAvatarList"), pAccount_onReqAvatarList); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_onReqAvatarList->aliasID, pAccount_onReqAvatarList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(onReqAvatarList / 10003).");

	TArray<DATATYPE_BASE*> Account_reqAvatarList_args;

	Method* pAccount_reqAvatarList = new Method();
	pAccount_reqAvatarList->name = TEXT("reqAvatarList");
	pAccount_reqAvatarList->methodUtype = 10001;
	pAccount_reqAvatarList->aliasID = -1;
	pAccount_reqAvatarList->args = Account_reqAvatarList_args;

	pAccountModule->methods.Add(TEXT("reqAvatarList"), pAccount_reqAvatarList); 
	pAccountModule->base_methods.Add(TEXT("reqAvatarList"), pAccount_reqAvatarList);

	pAccountModule->idbase_methods.Add(pAccount_reqAvatarList->methodUtype, pAccount_reqAvatarList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqAvatarList / 10001).");

	TArray<DATATYPE_BASE*> Account_reqCreateAvatar_args;
	Account_reqCreateAvatar_args.Add(EntityDef::id2datatypes[2]);
	Account_reqCreateAvatar_args.Add(EntityDef::id2datatypes[12]);

	Method* pAccount_reqCreateAvatar = new Method();
	pAccount_reqCreateAvatar->name = TEXT("reqCreateAvatar");
	pAccount_reqCreateAvatar->methodUtype = 10002;
	pAccount_reqCreateAvatar->aliasID = -1;
	pAccount_reqCreateAvatar->args = Account_reqCreateAvatar_args;

	pAccountModule->methods.Add(TEXT("reqCreateAvatar"), pAccount_reqCreateAvatar); 
	pAccountModule->base_methods.Add(TEXT("reqCreateAvatar"), pAccount_reqCreateAvatar);

	pAccountModule->idbase_methods.Add(pAccount_reqCreateAvatar->methodUtype, pAccount_reqCreateAvatar);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqCreateAvatar / 10002).");

	TArray<DATATYPE_BASE*> Account_reqRemoveAvatar_args;
	Account_reqRemoveAvatar_args.Add(EntityDef::id2datatypes[12]);

	Method* pAccount_reqRemoveAvatar = new Method();
	pAccount_reqRemoveAvatar->name = TEXT("reqRemoveAvatar");
	pAccount_reqRemoveAvatar->methodUtype = 1;
	pAccount_reqRemoveAvatar->aliasID = -1;
	pAccount_reqRemoveAvatar->args = Account_reqRemoveAvatar_args;

	pAccountModule->methods.Add(TEXT("reqRemoveAvatar"), pAccount_reqRemoveAvatar); 
	pAccountModule->base_methods.Add(TEXT("reqRemoveAvatar"), pAccount_reqRemoveAvatar);

	pAccountModule->idbase_methods.Add(pAccount_reqRemoveAvatar->methodUtype, pAccount_reqRemoveAvatar);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqRemoveAvatar / 1).");

	TArray<DATATYPE_BASE*> Account_reqRemoveAvatarDBID_args;
	Account_reqRemoveAvatarDBID_args.Add(EntityDef::id2datatypes[5]);

	Method* pAccount_reqRemoveAvatarDBID = new Method();
	pAccount_reqRemoveAvatarDBID->name = TEXT("reqRemoveAvatarDBID");
	pAccount_reqRemoveAvatarDBID->methodUtype = 2;
	pAccount_reqRemoveAvatarDBID->aliasID = -1;
	pAccount_reqRemoveAvatarDBID->args = Account_reqRemoveAvatarDBID_args;

	pAccountModule->methods.Add(TEXT("reqRemoveAvatarDBID"), pAccount_reqRemoveAvatarDBID); 
	pAccountModule->base_methods.Add(TEXT("reqRemoveAvatarDBID"), pAccount_reqRemoveAvatarDBID);

	pAccountModule->idbase_methods.Add(pAccount_reqRemoveAvatarDBID->methodUtype, pAccount_reqRemoveAvatarDBID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqRemoveAvatarDBID / 2).");

	TArray<DATATYPE_BASE*> Account_selectAvatarGame_args;
	Account_selectAvatarGame_args.Add(EntityDef::id2datatypes[5]);

	Method* pAccount_selectAvatarGame = new Method();
	pAccount_selectAvatarGame->name = TEXT("selectAvatarGame");
	pAccount_selectAvatarGame->methodUtype = 10004;
	pAccount_selectAvatarGame->aliasID = -1;
	pAccount_selectAvatarGame->args = Account_selectAvatarGame_args;

	pAccountModule->methods.Add(TEXT("selectAvatarGame"), pAccount_selectAvatarGame); 
	pAccountModule->base_methods.Add(TEXT("selectAvatarGame"), pAccount_selectAvatarGame);

	pAccountModule->idbase_methods.Add(pAccount_selectAvatarGame->methodUtype, pAccount_selectAvatarGame);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(selectAvatarGame / 10004).");

	ScriptModule* pAvatarModule = new ScriptModule("Avatar", 2);
	EntityDef::moduledefs.Add(TEXT("Avatar"), pAvatarModule);
	EntityDef::idmoduledefs.Add(2, pAvatarModule);

	Property* pAvatar_position = new Property();
	pAvatar_position->name = TEXT("position");
	pAvatar_position->properUtype = 40000;
	pAvatar_position->properFlags = 4;
	pAvatar_position->aliasID = 1;
	KBVar* pAvatar_position_defval = new KBVar(FVector());
	pAvatar_position->pDefaultVal = pAvatar_position_defval;
	pAvatarModule->propertys.Add(TEXT("position"), pAvatar_position); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_position->aliasID, pAvatar_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(position / 40000).");

	Property* pAvatar_direction = new Property();
	pAvatar_direction->name = TEXT("direction");
	pAvatar_direction->properUtype = 40001;
	pAvatar_direction->properFlags = 4;
	pAvatar_direction->aliasID = 2;
	KBVar* pAvatar_direction_defval = new KBVar(FVector());
	pAvatar_direction->pDefaultVal = pAvatar_direction_defval;
	pAvatarModule->propertys.Add(TEXT("direction"), pAvatar_direction); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_direction->aliasID, pAvatar_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(direction / 40001).");

	Property* pAvatar_spaceID = new Property();
	pAvatar_spaceID->name = TEXT("spaceID");
	pAvatar_spaceID->properUtype = 40002;
	pAvatar_spaceID->properFlags = 16;
	pAvatar_spaceID->aliasID = 3;
	KBVar* pAvatar_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pAvatar_spaceID->pDefaultVal = pAvatar_spaceID_defval;
	pAvatarModule->propertys.Add(TEXT("spaceID"), pAvatar_spaceID); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_spaceID->aliasID, pAvatar_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(spaceID / 40002).");

	Property* pAvatar_HP = new Property();
	pAvatar_HP->name = TEXT("HP");
	pAvatar_HP->properUtype = 47001;
	pAvatar_HP->properFlags = 4;
	pAvatar_HP->aliasID = 4;
	KBVar* pAvatar_HP_defval = new KBVar((int32)FCString::Atoi64(TEXT("0")));
	pAvatar_HP->pDefaultVal = pAvatar_HP_defval;
	pAvatarModule->propertys.Add(TEXT("HP"), pAvatar_HP); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_HP->aliasID, pAvatar_HP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(HP / 47001).");

	Property* pAvatar_HP_Max = new Property();
	pAvatar_HP_Max->name = TEXT("HP_Max");
	pAvatar_HP_Max->properUtype = 47002;
	pAvatar_HP_Max->properFlags = 4;
	pAvatar_HP_Max->aliasID = 5;
	KBVar* pAvatar_HP_Max_defval = new KBVar((int32)FCString::Atoi64(TEXT("0")));
	pAvatar_HP_Max->pDefaultVal = pAvatar_HP_Max_defval;
	pAvatarModule->propertys.Add(TEXT("HP_Max"), pAvatar_HP_Max); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_HP_Max->aliasID, pAvatar_HP_Max);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(HP_Max / 47002).");

	Property* pAvatar_MP = new Property();
	pAvatar_MP->name = TEXT("MP");
	pAvatar_MP->properUtype = 47003;
	pAvatar_MP->properFlags = 4;
	pAvatar_MP->aliasID = 6;
	KBVar* pAvatar_MP_defval = new KBVar((int32)FCString::Atoi64(TEXT("0")));
	pAvatar_MP->pDefaultVal = pAvatar_MP_defval;
	pAvatarModule->propertys.Add(TEXT("MP"), pAvatar_MP); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_MP->aliasID, pAvatar_MP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(MP / 47003).");

	Property* pAvatar_MP_Max = new Property();
	pAvatar_MP_Max->name = TEXT("MP_Max");
	pAvatar_MP_Max->properUtype = 47004;
	pAvatar_MP_Max->properFlags = 4;
	pAvatar_MP_Max->aliasID = 7;
	KBVar* pAvatar_MP_Max_defval = new KBVar((int32)FCString::Atoi64(TEXT("0")));
	pAvatar_MP_Max->pDefaultVal = pAvatar_MP_Max_defval;
	pAvatarModule->propertys.Add(TEXT("MP_Max"), pAvatar_MP_Max); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_MP_Max->aliasID, pAvatar_MP_Max);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(MP_Max / 47004).");

	Property* pAvatar_component1 = new Property();
	pAvatar_component1->name = TEXT("component1");
	pAvatar_component1->properUtype = 16;
	pAvatar_component1->properFlags = 253;
	pAvatar_component1->aliasID = 8;
	pAvatarModule->propertys.Add(TEXT("component1"), pAvatar_component1); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_component1->aliasID, pAvatar_component1);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(component1 / 16).");

	Property* pAvatar_component2 = new Property();
	pAvatar_component2->name = TEXT("component2");
	pAvatar_component2->properUtype = 21;
	pAvatar_component2->properFlags = 97;
	pAvatar_component2->aliasID = 9;
	pAvatarModule->propertys.Add(TEXT("component2"), pAvatar_component2); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_component2->aliasID, pAvatar_component2);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(component2 / 21).");

	Property* pAvatar_component3 = new Property();
	pAvatar_component3->name = TEXT("component3");
	pAvatar_component3->properUtype = 22;
	pAvatar_component3->properFlags = 157;
	pAvatar_component3->aliasID = 10;
	pAvatarModule->propertys.Add(TEXT("component3"), pAvatar_component3); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_component3->aliasID, pAvatar_component3);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(component3 / 22).");

	Property* pAvatar_forbids = new Property();
	pAvatar_forbids->name = TEXT("forbids");
	pAvatar_forbids->properUtype = 47005;
	pAvatar_forbids->properFlags = 4;
	pAvatar_forbids->aliasID = 11;
	KBVar* pAvatar_forbids_defval = new KBVar((int32)FCString::Atoi64(TEXT("0")));
	pAvatar_forbids->pDefaultVal = pAvatar_forbids_defval;
	pAvatarModule->propertys.Add(TEXT("forbids"), pAvatar_forbids); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_forbids->aliasID, pAvatar_forbids);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(forbids / 47005).");

	Property* pAvatar_level = new Property();
	pAvatar_level->name = TEXT("level");
	pAvatar_level->properUtype = 41002;
	pAvatar_level->properFlags = 8;
	pAvatar_level->aliasID = 12;
	KBVar* pAvatar_level_defval = new KBVar((uint16)FCString::Atoi64(TEXT("")));
	pAvatar_level->pDefaultVal = pAvatar_level_defval;
	pAvatarModule->propertys.Add(TEXT("level"), pAvatar_level); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_level->aliasID, pAvatar_level);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(level / 41002).");

	Property* pAvatar_modelID = new Property();
	pAvatar_modelID->name = TEXT("modelID");
	pAvatar_modelID->properUtype = 41006;
	pAvatar_modelID->properFlags = 4;
	pAvatar_modelID->aliasID = 13;
	KBVar* pAvatar_modelID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pAvatar_modelID->pDefaultVal = pAvatar_modelID_defval;
	pAvatarModule->propertys.Add(TEXT("modelID"), pAvatar_modelID); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_modelID->aliasID, pAvatar_modelID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(modelID / 41006).");

	Property* pAvatar_modelScale = new Property();
	pAvatar_modelScale->name = TEXT("modelScale");
	pAvatar_modelScale->properUtype = 41007;
	pAvatar_modelScale->properFlags = 4;
	pAvatar_modelScale->aliasID = 14;
	KBVar* pAvatar_modelScale_defval = new KBVar((uint8)FCString::Atoi64(TEXT("30")));
	pAvatar_modelScale->pDefaultVal = pAvatar_modelScale_defval;
	pAvatarModule->propertys.Add(TEXT("modelScale"), pAvatar_modelScale); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_modelScale->aliasID, pAvatar_modelScale);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(modelScale / 41007).");

	Property* pAvatar_moveSpeed = new Property();
	pAvatar_moveSpeed->name = TEXT("moveSpeed");
	pAvatar_moveSpeed->properUtype = 11;
	pAvatar_moveSpeed->properFlags = 4;
	pAvatar_moveSpeed->aliasID = 15;
	KBVar* pAvatar_moveSpeed_defval = new KBVar((uint8)FCString::Atoi64(TEXT("50")));
	pAvatar_moveSpeed->pDefaultVal = pAvatar_moveSpeed_defval;
	pAvatarModule->propertys.Add(TEXT("moveSpeed"), pAvatar_moveSpeed); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_moveSpeed->aliasID, pAvatar_moveSpeed);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(moveSpeed / 11).");

	Property* pAvatar_name = new Property();
	pAvatar_name->name = TEXT("name");
	pAvatar_name->properUtype = 41003;
	pAvatar_name->properFlags = 4;
	pAvatar_name->aliasID = 16;
	KBVar* pAvatar_name_defval = new KBVar(FString());
	pAvatar_name->pDefaultVal = pAvatar_name_defval;
	pAvatarModule->propertys.Add(TEXT("name"), pAvatar_name); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_name->aliasID, pAvatar_name);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(name / 41003).");

	Property* pAvatar_own_val = new Property();
	pAvatar_own_val->name = TEXT("own_val");
	pAvatar_own_val->properUtype = 6;
	pAvatar_own_val->properFlags = 16;
	pAvatar_own_val->aliasID = 17;
	KBVar* pAvatar_own_val_defval = new KBVar((uint16)FCString::Atoi64(TEXT("")));
	pAvatar_own_val->pDefaultVal = pAvatar_own_val_defval;
	pAvatarModule->propertys.Add(TEXT("own_val"), pAvatar_own_val); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_own_val->aliasID, pAvatar_own_val);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(own_val / 6).");

	Property* pAvatar_spaceUType = new Property();
	pAvatar_spaceUType->name = TEXT("spaceUType");
	pAvatar_spaceUType->properUtype = 41001;
	pAvatar_spaceUType->properFlags = 8;
	pAvatar_spaceUType->aliasID = 18;
	KBVar* pAvatar_spaceUType_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pAvatar_spaceUType->pDefaultVal = pAvatar_spaceUType_defval;
	pAvatarModule->propertys.Add(TEXT("spaceUType"), pAvatar_spaceUType); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_spaceUType->aliasID, pAvatar_spaceUType);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(spaceUType / 41001).");

	Property* pAvatar_state = new Property();
	pAvatar_state->name = TEXT("state");
	pAvatar_state->properUtype = 47006;
	pAvatar_state->properFlags = 4;
	pAvatar_state->aliasID = 19;
	KBVar* pAvatar_state_defval = new KBVar((int8)FCString::Atoi64(TEXT("0")));
	pAvatar_state->pDefaultVal = pAvatar_state_defval;
	pAvatarModule->propertys.Add(TEXT("state"), pAvatar_state); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_state->aliasID, pAvatar_state);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(state / 47006).");

	Property* pAvatar_subState = new Property();
	pAvatar_subState->name = TEXT("subState");
	pAvatar_subState->properUtype = 47007;
	pAvatar_subState->properFlags = 4;
	pAvatar_subState->aliasID = 20;
	KBVar* pAvatar_subState_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pAvatar_subState->pDefaultVal = pAvatar_subState_defval;
	pAvatarModule->propertys.Add(TEXT("subState"), pAvatar_subState); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_subState->aliasID, pAvatar_subState);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(subState / 47007).");

	Property* pAvatar_uid = new Property();
	pAvatar_uid->name = TEXT("uid");
	pAvatar_uid->properUtype = 41004;
	pAvatar_uid->properFlags = 4;
	pAvatar_uid->aliasID = 21;
	KBVar* pAvatar_uid_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pAvatar_uid->pDefaultVal = pAvatar_uid_defval;
	pAvatarModule->propertys.Add(TEXT("uid"), pAvatar_uid); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_uid->aliasID, pAvatar_uid);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(uid / 41004).");

	Property* pAvatar_utype = new Property();
	pAvatar_utype->name = TEXT("utype");
	pAvatar_utype->properUtype = 41005;
	pAvatar_utype->properFlags = 4;
	pAvatar_utype->aliasID = 22;
	KBVar* pAvatar_utype_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pAvatar_utype->pDefaultVal = pAvatar_utype_defval;
	pAvatarModule->propertys.Add(TEXT("utype"), pAvatar_utype); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_utype->aliasID, pAvatar_utype);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(utype / 41005).");

	TArray<DATATYPE_BASE*> Avatar_dialog_addOption_args;
	Avatar_dialog_addOption_args.Add(EntityDef::id2datatypes[2]);
	Avatar_dialog_addOption_args.Add(EntityDef::id2datatypes[4]);
	Avatar_dialog_addOption_args.Add(EntityDef::id2datatypes[12]);
	Avatar_dialog_addOption_args.Add(EntityDef::id2datatypes[8]);

	Method* pAvatar_dialog_addOption = new Method();
	pAvatar_dialog_addOption->name = TEXT("dialog_addOption");
	pAvatar_dialog_addOption->methodUtype = 10101;
	pAvatar_dialog_addOption->aliasID = 1;
	pAvatar_dialog_addOption->args = Avatar_dialog_addOption_args;

	pAvatarModule->methods.Add(TEXT("dialog_addOption"), pAvatar_dialog_addOption); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_dialog_addOption->aliasID, pAvatar_dialog_addOption);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(dialog_addOption / 10101).");

	TArray<DATATYPE_BASE*> Avatar_dialog_close_args;

	Method* pAvatar_dialog_close = new Method();
	pAvatar_dialog_close->name = TEXT("dialog_close");
	pAvatar_dialog_close->methodUtype = 10104;
	pAvatar_dialog_close->aliasID = 2;
	pAvatar_dialog_close->args = Avatar_dialog_close_args;

	pAvatarModule->methods.Add(TEXT("dialog_close"), pAvatar_dialog_close); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_dialog_close->aliasID, pAvatar_dialog_close);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(dialog_close / 10104).");

	TArray<DATATYPE_BASE*> Avatar_dialog_setText_args;
	Avatar_dialog_setText_args.Add(EntityDef::id2datatypes[12]);
	Avatar_dialog_setText_args.Add(EntityDef::id2datatypes[2]);
	Avatar_dialog_setText_args.Add(EntityDef::id2datatypes[4]);
	Avatar_dialog_setText_args.Add(EntityDef::id2datatypes[12]);

	Method* pAvatar_dialog_setText = new Method();
	pAvatar_dialog_setText->name = TEXT("dialog_setText");
	pAvatar_dialog_setText->methodUtype = 10102;
	pAvatar_dialog_setText->aliasID = 3;
	pAvatar_dialog_setText->args = Avatar_dialog_setText_args;

	pAvatarModule->methods.Add(TEXT("dialog_setText"), pAvatar_dialog_setText); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_dialog_setText->aliasID, pAvatar_dialog_setText);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(dialog_setText / 10102).");

	TArray<DATATYPE_BASE*> Avatar_onAddSkill_args;
	Avatar_onAddSkill_args.Add(EntityDef::id2datatypes[8]);

	Method* pAvatar_onAddSkill = new Method();
	pAvatar_onAddSkill->name = TEXT("onAddSkill");
	pAvatar_onAddSkill->methodUtype = 12;
	pAvatar_onAddSkill->aliasID = 4;
	pAvatar_onAddSkill->args = Avatar_onAddSkill_args;

	pAvatarModule->methods.Add(TEXT("onAddSkill"), pAvatar_onAddSkill); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_onAddSkill->aliasID, pAvatar_onAddSkill);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(onAddSkill / 12).");

	TArray<DATATYPE_BASE*> Avatar_onJump_args;

	Method* pAvatar_onJump = new Method();
	pAvatar_onJump->name = TEXT("onJump");
	pAvatar_onJump->methodUtype = 7;
	pAvatar_onJump->aliasID = 5;
	pAvatar_onJump->args = Avatar_onJump_args;

	pAvatarModule->methods.Add(TEXT("onJump"), pAvatar_onJump); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_onJump->aliasID, pAvatar_onJump);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(onJump / 7).");

	TArray<DATATYPE_BASE*> Avatar_onRemoveSkill_args;
	Avatar_onRemoveSkill_args.Add(EntityDef::id2datatypes[8]);

	Method* pAvatar_onRemoveSkill = new Method();
	pAvatar_onRemoveSkill->name = TEXT("onRemoveSkill");
	pAvatar_onRemoveSkill->methodUtype = 13;
	pAvatar_onRemoveSkill->aliasID = 6;
	pAvatar_onRemoveSkill->args = Avatar_onRemoveSkill_args;

	pAvatarModule->methods.Add(TEXT("onRemoveSkill"), pAvatar_onRemoveSkill); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_onRemoveSkill->aliasID, pAvatar_onRemoveSkill);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(onRemoveSkill / 13).");

	TArray<DATATYPE_BASE*> Avatar_recvDamage_args;
	Avatar_recvDamage_args.Add(EntityDef::id2datatypes[8]);
	Avatar_recvDamage_args.Add(EntityDef::id2datatypes[8]);
	Avatar_recvDamage_args.Add(EntityDef::id2datatypes[8]);
	Avatar_recvDamage_args.Add(EntityDef::id2datatypes[8]);

	Method* pAvatar_recvDamage = new Method();
	pAvatar_recvDamage->name = TEXT("recvDamage");
	pAvatar_recvDamage->methodUtype = 16;
	pAvatar_recvDamage->aliasID = 7;
	pAvatar_recvDamage->args = Avatar_recvDamage_args;

	pAvatarModule->methods.Add(TEXT("recvDamage"), pAvatar_recvDamage); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_recvDamage->aliasID, pAvatar_recvDamage);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(recvDamage / 16).");

	TArray<DATATYPE_BASE*> Avatar_dialog_args;
	Avatar_dialog_args.Add(EntityDef::id2datatypes[8]);
	Avatar_dialog_args.Add(EntityDef::id2datatypes[4]);

	Method* pAvatar_dialog = new Method();
	pAvatar_dialog->name = TEXT("dialog");
	pAvatar_dialog->methodUtype = 11003;
	pAvatar_dialog->aliasID = -1;
	pAvatar_dialog->args = Avatar_dialog_args;

	pAvatarModule->methods.Add(TEXT("dialog"), pAvatar_dialog); 
	pAvatarModule->cell_methods.Add(TEXT("dialog"), pAvatar_dialog);

	pAvatarModule->idcell_methods.Add(pAvatar_dialog->methodUtype, pAvatar_dialog);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(dialog / 11003).");

	TArray<DATATYPE_BASE*> Avatar_jump_args;

	Method* pAvatar_jump = new Method();
	pAvatar_jump->name = TEXT("jump");
	pAvatar_jump->methodUtype = 5;
	pAvatar_jump->aliasID = -1;
	pAvatar_jump->args = Avatar_jump_args;

	pAvatarModule->methods.Add(TEXT("jump"), pAvatar_jump); 
	pAvatarModule->cell_methods.Add(TEXT("jump"), pAvatar_jump);

	pAvatarModule->idcell_methods.Add(pAvatar_jump->methodUtype, pAvatar_jump);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(jump / 5).");

	TArray<DATATYPE_BASE*> Avatar_relive_args;
	Avatar_relive_args.Add(EntityDef::id2datatypes[2]);

	Method* pAvatar_relive = new Method();
	pAvatar_relive->name = TEXT("relive");
	pAvatar_relive->methodUtype = 4;
	pAvatar_relive->aliasID = -1;
	pAvatar_relive->args = Avatar_relive_args;

	pAvatarModule->methods.Add(TEXT("relive"), pAvatar_relive); 
	pAvatarModule->cell_methods.Add(TEXT("relive"), pAvatar_relive);

	pAvatarModule->idcell_methods.Add(pAvatar_relive->methodUtype, pAvatar_relive);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(relive / 4).");

	TArray<DATATYPE_BASE*> Avatar_requestPull_args;

	Method* pAvatar_requestPull = new Method();
	pAvatar_requestPull->name = TEXT("requestPull");
	pAvatar_requestPull->methodUtype = 11;
	pAvatar_requestPull->aliasID = -1;
	pAvatar_requestPull->args = Avatar_requestPull_args;

	pAvatarModule->methods.Add(TEXT("requestPull"), pAvatar_requestPull); 
	pAvatarModule->cell_methods.Add(TEXT("requestPull"), pAvatar_requestPull);

	pAvatarModule->idcell_methods.Add(pAvatar_requestPull->methodUtype, pAvatar_requestPull);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(requestPull / 11).");

	TArray<DATATYPE_BASE*> Avatar_useTargetSkill_args;
	Avatar_useTargetSkill_args.Add(EntityDef::id2datatypes[8]);
	Avatar_useTargetSkill_args.Add(EntityDef::id2datatypes[8]);

	Method* pAvatar_useTargetSkill = new Method();
	pAvatar_useTargetSkill->name = TEXT("useTargetSkill");
	pAvatar_useTargetSkill->methodUtype = 11001;
	pAvatar_useTargetSkill->aliasID = -1;
	pAvatar_useTargetSkill->args = Avatar_useTargetSkill_args;

	pAvatarModule->methods.Add(TEXT("useTargetSkill"), pAvatar_useTargetSkill); 
	pAvatarModule->cell_methods.Add(TEXT("useTargetSkill"), pAvatar_useTargetSkill);

	pAvatarModule->idcell_methods.Add(pAvatar_useTargetSkill->methodUtype, pAvatar_useTargetSkill);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(useTargetSkill / 11001).");

	ScriptModule* pTestModule = new ScriptModule("Test", 3);
	EntityDef::moduledefs.Add(TEXT("Test"), pTestModule);
	EntityDef::idmoduledefs.Add(3, pTestModule);

	Property* pTest_position = new Property();
	pTest_position->name = TEXT("position");
	pTest_position->properUtype = 40000;
	pTest_position->properFlags = 4;
	pTest_position->aliasID = 1;
	KBVar* pTest_position_defval = new KBVar(FVector());
	pTest_position->pDefaultVal = pTest_position_defval;
	pTestModule->propertys.Add(TEXT("position"), pTest_position); 

	pTestModule->usePropertyDescrAlias = true;
	pTestModule->idpropertys.Add((uint16)pTest_position->aliasID, pTest_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Test), property(position / 40000).");

	Property* pTest_direction = new Property();
	pTest_direction->name = TEXT("direction");
	pTest_direction->properUtype = 40001;
	pTest_direction->properFlags = 4;
	pTest_direction->aliasID = 2;
	KBVar* pTest_direction_defval = new KBVar(FVector());
	pTest_direction->pDefaultVal = pTest_direction_defval;
	pTestModule->propertys.Add(TEXT("direction"), pTest_direction); 

	pTestModule->usePropertyDescrAlias = true;
	pTestModule->idpropertys.Add((uint16)pTest_direction->aliasID, pTest_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Test), property(direction / 40001).");

	Property* pTest_spaceID = new Property();
	pTest_spaceID->name = TEXT("spaceID");
	pTest_spaceID->properUtype = 40002;
	pTest_spaceID->properFlags = 16;
	pTest_spaceID->aliasID = 3;
	KBVar* pTest_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pTest_spaceID->pDefaultVal = pTest_spaceID_defval;
	pTestModule->propertys.Add(TEXT("spaceID"), pTest_spaceID); 

	pTestModule->usePropertyDescrAlias = true;
	pTestModule->idpropertys.Add((uint16)pTest_spaceID->aliasID, pTest_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Test), property(spaceID / 40002).");

	Property* pTest_own = new Property();
	pTest_own->name = TEXT("own");
	pTest_own->properUtype = 18;
	pTest_own->properFlags = 8;
	pTest_own->aliasID = 4;
	KBVar* pTest_own_defval = new KBVar((int32)FCString::Atoi64(TEXT("1001")));
	pTest_own->pDefaultVal = pTest_own_defval;
	pTestModule->propertys.Add(TEXT("own"), pTest_own); 

	pTestModule->usePropertyDescrAlias = true;
	pTestModule->idpropertys.Add((uint16)pTest_own->aliasID, pTest_own);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Test), property(own / 18).");

	Property* pTest_state = new Property();
	pTest_state->name = TEXT("state");
	pTest_state->properUtype = 17;
	pTest_state->properFlags = 4;
	pTest_state->aliasID = 5;
	KBVar* pTest_state_defval = new KBVar((int32)FCString::Atoi64(TEXT("100")));
	pTest_state->pDefaultVal = pTest_state_defval;
	pTestModule->propertys.Add(TEXT("state"), pTest_state); 

	pTestModule->usePropertyDescrAlias = true;
	pTestModule->idpropertys.Add((uint16)pTest_state->aliasID, pTest_state);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Test), property(state / 17).");

	TArray<DATATYPE_BASE*> Test_helloCB_args;
	Test_helloCB_args.Add(EntityDef::id2datatypes[8]);

	Method* pTest_helloCB = new Method();
	pTest_helloCB->name = TEXT("helloCB");
	pTest_helloCB->methodUtype = 28;
	pTest_helloCB->aliasID = 1;
	pTest_helloCB->args = Test_helloCB_args;

	pTestModule->methods.Add(TEXT("helloCB"), pTest_helloCB); 
	pTestModule->useMethodDescrAlias = true;
	pTestModule->idmethods.Add((uint16)pTest_helloCB->aliasID, pTest_helloCB);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Test), method(helloCB / 28).");

	TArray<DATATYPE_BASE*> Test_say_args;
	Test_say_args.Add(EntityDef::id2datatypes[8]);

	Method* pTest_say = new Method();
	pTest_say->name = TEXT("say");
	pTest_say->methodUtype = 27;
	pTest_say->aliasID = -1;
	pTest_say->args = Test_say_args;

	pTestModule->methods.Add(TEXT("say"), pTest_say); 
	pTestModule->base_methods.Add(TEXT("say"), pTest_say);

	pTestModule->idbase_methods.Add(pTest_say->methodUtype, pTest_say);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Test), method(say / 27).");

	TArray<DATATYPE_BASE*> Test_hello_args;
	Test_hello_args.Add(EntityDef::id2datatypes[8]);

	Method* pTest_hello = new Method();
	pTest_hello->name = TEXT("hello");
	pTest_hello->methodUtype = 26;
	pTest_hello->aliasID = -1;
	pTest_hello->args = Test_hello_args;

	pTestModule->methods.Add(TEXT("hello"), pTest_hello); 
	pTestModule->cell_methods.Add(TEXT("hello"), pTest_hello);

	pTestModule->idcell_methods.Add(pTest_hello->methodUtype, pTest_hello);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Test), method(hello / 26).");

	ScriptModule* pTestNoBaseModule = new ScriptModule("TestNoBase", 4);
	EntityDef::moduledefs.Add(TEXT("TestNoBase"), pTestNoBaseModule);
	EntityDef::idmoduledefs.Add(4, pTestNoBaseModule);

	Property* pTestNoBase_position = new Property();
	pTestNoBase_position->name = TEXT("position");
	pTestNoBase_position->properUtype = 40000;
	pTestNoBase_position->properFlags = 4;
	pTestNoBase_position->aliasID = 1;
	KBVar* pTestNoBase_position_defval = new KBVar(FVector());
	pTestNoBase_position->pDefaultVal = pTestNoBase_position_defval;
	pTestNoBaseModule->propertys.Add(TEXT("position"), pTestNoBase_position); 

	pTestNoBaseModule->usePropertyDescrAlias = true;
	pTestNoBaseModule->idpropertys.Add((uint16)pTestNoBase_position->aliasID, pTestNoBase_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(TestNoBase), property(position / 40000).");

	Property* pTestNoBase_direction = new Property();
	pTestNoBase_direction->name = TEXT("direction");
	pTestNoBase_direction->properUtype = 40001;
	pTestNoBase_direction->properFlags = 4;
	pTestNoBase_direction->aliasID = 2;
	KBVar* pTestNoBase_direction_defval = new KBVar(FVector());
	pTestNoBase_direction->pDefaultVal = pTestNoBase_direction_defval;
	pTestNoBaseModule->propertys.Add(TEXT("direction"), pTestNoBase_direction); 

	pTestNoBaseModule->usePropertyDescrAlias = true;
	pTestNoBaseModule->idpropertys.Add((uint16)pTestNoBase_direction->aliasID, pTestNoBase_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(TestNoBase), property(direction / 40001).");

	Property* pTestNoBase_spaceID = new Property();
	pTestNoBase_spaceID->name = TEXT("spaceID");
	pTestNoBase_spaceID->properUtype = 40002;
	pTestNoBase_spaceID->properFlags = 16;
	pTestNoBase_spaceID->aliasID = 3;
	KBVar* pTestNoBase_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pTestNoBase_spaceID->pDefaultVal = pTestNoBase_spaceID_defval;
	pTestNoBaseModule->propertys.Add(TEXT("spaceID"), pTestNoBase_spaceID); 

	pTestNoBaseModule->usePropertyDescrAlias = true;
	pTestNoBaseModule->idpropertys.Add((uint16)pTestNoBase_spaceID->aliasID, pTestNoBase_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(TestNoBase), property(spaceID / 40002).");

	Property* pTestNoBase_own = new Property();
	pTestNoBase_own->name = TEXT("own");
	pTestNoBase_own->properUtype = 24;
	pTestNoBase_own->properFlags = 8;
	pTestNoBase_own->aliasID = 4;
	KBVar* pTestNoBase_own_defval = new KBVar((int32)FCString::Atoi64(TEXT("1001")));
	pTestNoBase_own->pDefaultVal = pTestNoBase_own_defval;
	pTestNoBaseModule->propertys.Add(TEXT("own"), pTestNoBase_own); 

	pTestNoBaseModule->usePropertyDescrAlias = true;
	pTestNoBaseModule->idpropertys.Add((uint16)pTestNoBase_own->aliasID, pTestNoBase_own);

	//DEBUG_MSG("EntityDef::initScriptModules: add(TestNoBase), property(own / 24).");

	Property* pTestNoBase_state = new Property();
	pTestNoBase_state->name = TEXT("state");
	pTestNoBase_state->properUtype = 23;
	pTestNoBase_state->properFlags = 4;
	pTestNoBase_state->aliasID = 5;
	KBVar* pTestNoBase_state_defval = new KBVar((int32)FCString::Atoi64(TEXT("100")));
	pTestNoBase_state->pDefaultVal = pTestNoBase_state_defval;
	pTestNoBaseModule->propertys.Add(TEXT("state"), pTestNoBase_state); 

	pTestNoBaseModule->usePropertyDescrAlias = true;
	pTestNoBaseModule->idpropertys.Add((uint16)pTestNoBase_state->aliasID, pTestNoBase_state);

	//DEBUG_MSG("EntityDef::initScriptModules: add(TestNoBase), property(state / 23).");

	TArray<DATATYPE_BASE*> TestNoBase_helloCB_args;
	TestNoBase_helloCB_args.Add(EntityDef::id2datatypes[8]);

	Method* pTestNoBase_helloCB = new Method();
	pTestNoBase_helloCB->name = TEXT("helloCB");
	pTestNoBase_helloCB->methodUtype = 30;
	pTestNoBase_helloCB->aliasID = 1;
	pTestNoBase_helloCB->args = TestNoBase_helloCB_args;

	pTestNoBaseModule->methods.Add(TEXT("helloCB"), pTestNoBase_helloCB); 
	pTestNoBaseModule->useMethodDescrAlias = true;
	pTestNoBaseModule->idmethods.Add((uint16)pTestNoBase_helloCB->aliasID, pTestNoBase_helloCB);

	//DEBUG_MSG("EntityDef::initScriptModules: add(TestNoBase), method(helloCB / 30).");

	TArray<DATATYPE_BASE*> TestNoBase_hello_args;
	TestNoBase_hello_args.Add(EntityDef::id2datatypes[8]);

	Method* pTestNoBase_hello = new Method();
	pTestNoBase_hello->name = TEXT("hello");
	pTestNoBase_hello->methodUtype = 29;
	pTestNoBase_hello->aliasID = -1;
	pTestNoBase_hello->args = TestNoBase_hello_args;

	pTestNoBaseModule->methods.Add(TEXT("hello"), pTestNoBase_hello); 
	pTestNoBaseModule->cell_methods.Add(TEXT("hello"), pTestNoBase_hello);

	pTestNoBaseModule->idcell_methods.Add(pTestNoBase_hello->methodUtype, pTestNoBase_hello);

	//DEBUG_MSG("EntityDef::initScriptModules: add(TestNoBase), method(hello / 29).");

	ScriptModule* pMonsterModule = new ScriptModule("Monster", 5);
	EntityDef::moduledefs.Add(TEXT("Monster"), pMonsterModule);
	EntityDef::idmoduledefs.Add(5, pMonsterModule);

	Property* pMonster_position = new Property();
	pMonster_position->name = TEXT("position");
	pMonster_position->properUtype = 40000;
	pMonster_position->properFlags = 4;
	pMonster_position->aliasID = 1;
	KBVar* pMonster_position_defval = new KBVar(FVector());
	pMonster_position->pDefaultVal = pMonster_position_defval;
	pMonsterModule->propertys.Add(TEXT("position"), pMonster_position); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_position->aliasID, pMonster_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(position / 40000).");

	Property* pMonster_direction = new Property();
	pMonster_direction->name = TEXT("direction");
	pMonster_direction->properUtype = 40001;
	pMonster_direction->properFlags = 4;
	pMonster_direction->aliasID = 2;
	KBVar* pMonster_direction_defval = new KBVar(FVector());
	pMonster_direction->pDefaultVal = pMonster_direction_defval;
	pMonsterModule->propertys.Add(TEXT("direction"), pMonster_direction); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_direction->aliasID, pMonster_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(direction / 40001).");

	Property* pMonster_spaceID = new Property();
	pMonster_spaceID->name = TEXT("spaceID");
	pMonster_spaceID->properUtype = 40002;
	pMonster_spaceID->properFlags = 16;
	pMonster_spaceID->aliasID = 3;
	KBVar* pMonster_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pMonster_spaceID->pDefaultVal = pMonster_spaceID_defval;
	pMonsterModule->propertys.Add(TEXT("spaceID"), pMonster_spaceID); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_spaceID->aliasID, pMonster_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(spaceID / 40002).");

	Property* pMonster_HP = new Property();
	pMonster_HP->name = TEXT("HP");
	pMonster_HP->properUtype = 47001;
	pMonster_HP->properFlags = 4;
	pMonster_HP->aliasID = 4;
	KBVar* pMonster_HP_defval = new KBVar((int32)FCString::Atoi64(TEXT("0")));
	pMonster_HP->pDefaultVal = pMonster_HP_defval;
	pMonsterModule->propertys.Add(TEXT("HP"), pMonster_HP); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_HP->aliasID, pMonster_HP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(HP / 47001).");

	Property* pMonster_HP_Max = new Property();
	pMonster_HP_Max->name = TEXT("HP_Max");
	pMonster_HP_Max->properUtype = 47002;
	pMonster_HP_Max->properFlags = 4;
	pMonster_HP_Max->aliasID = 5;
	KBVar* pMonster_HP_Max_defval = new KBVar((int32)FCString::Atoi64(TEXT("0")));
	pMonster_HP_Max->pDefaultVal = pMonster_HP_Max_defval;
	pMonsterModule->propertys.Add(TEXT("HP_Max"), pMonster_HP_Max); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_HP_Max->aliasID, pMonster_HP_Max);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(HP_Max / 47002).");

	Property* pMonster_MP = new Property();
	pMonster_MP->name = TEXT("MP");
	pMonster_MP->properUtype = 47003;
	pMonster_MP->properFlags = 4;
	pMonster_MP->aliasID = 6;
	KBVar* pMonster_MP_defval = new KBVar((int32)FCString::Atoi64(TEXT("0")));
	pMonster_MP->pDefaultVal = pMonster_MP_defval;
	pMonsterModule->propertys.Add(TEXT("MP"), pMonster_MP); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_MP->aliasID, pMonster_MP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(MP / 47003).");

	Property* pMonster_MP_Max = new Property();
	pMonster_MP_Max->name = TEXT("MP_Max");
	pMonster_MP_Max->properUtype = 47004;
	pMonster_MP_Max->properFlags = 4;
	pMonster_MP_Max->aliasID = 7;
	KBVar* pMonster_MP_Max_defval = new KBVar((int32)FCString::Atoi64(TEXT("0")));
	pMonster_MP_Max->pDefaultVal = pMonster_MP_Max_defval;
	pMonsterModule->propertys.Add(TEXT("MP_Max"), pMonster_MP_Max); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_MP_Max->aliasID, pMonster_MP_Max);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(MP_Max / 47004).");

	Property* pMonster_entityNO = new Property();
	pMonster_entityNO->name = TEXT("entityNO");
	pMonster_entityNO->properUtype = 51007;
	pMonster_entityNO->properFlags = 4;
	pMonster_entityNO->aliasID = 8;
	KBVar* pMonster_entityNO_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pMonster_entityNO->pDefaultVal = pMonster_entityNO_defval;
	pMonsterModule->propertys.Add(TEXT("entityNO"), pMonster_entityNO); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_entityNO->aliasID, pMonster_entityNO);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(entityNO / 51007).");

	Property* pMonster_forbids = new Property();
	pMonster_forbids->name = TEXT("forbids");
	pMonster_forbids->properUtype = 47005;
	pMonster_forbids->properFlags = 4;
	pMonster_forbids->aliasID = 9;
	KBVar* pMonster_forbids_defval = new KBVar((int32)FCString::Atoi64(TEXT("0")));
	pMonster_forbids->pDefaultVal = pMonster_forbids_defval;
	pMonsterModule->propertys.Add(TEXT("forbids"), pMonster_forbids); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_forbids->aliasID, pMonster_forbids);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(forbids / 47005).");

	Property* pMonster_modelID = new Property();
	pMonster_modelID->name = TEXT("modelID");
	pMonster_modelID->properUtype = 41006;
	pMonster_modelID->properFlags = 4;
	pMonster_modelID->aliasID = 10;
	KBVar* pMonster_modelID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pMonster_modelID->pDefaultVal = pMonster_modelID_defval;
	pMonsterModule->propertys.Add(TEXT("modelID"), pMonster_modelID); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_modelID->aliasID, pMonster_modelID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(modelID / 41006).");

	Property* pMonster_modelScale = new Property();
	pMonster_modelScale->name = TEXT("modelScale");
	pMonster_modelScale->properUtype = 41007;
	pMonster_modelScale->properFlags = 4;
	pMonster_modelScale->aliasID = 11;
	KBVar* pMonster_modelScale_defval = new KBVar((uint8)FCString::Atoi64(TEXT("30")));
	pMonster_modelScale->pDefaultVal = pMonster_modelScale_defval;
	pMonsterModule->propertys.Add(TEXT("modelScale"), pMonster_modelScale); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_modelScale->aliasID, pMonster_modelScale);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(modelScale / 41007).");

	Property* pMonster_moveSpeed = new Property();
	pMonster_moveSpeed->name = TEXT("moveSpeed");
	pMonster_moveSpeed->properUtype = 32;
	pMonster_moveSpeed->properFlags = 4;
	pMonster_moveSpeed->aliasID = 12;
	KBVar* pMonster_moveSpeed_defval = new KBVar((uint8)FCString::Atoi64(TEXT("50")));
	pMonster_moveSpeed->pDefaultVal = pMonster_moveSpeed_defval;
	pMonsterModule->propertys.Add(TEXT("moveSpeed"), pMonster_moveSpeed); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_moveSpeed->aliasID, pMonster_moveSpeed);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(moveSpeed / 32).");

	Property* pMonster_name = new Property();
	pMonster_name->name = TEXT("name");
	pMonster_name->properUtype = 41003;
	pMonster_name->properFlags = 4;
	pMonster_name->aliasID = 13;
	KBVar* pMonster_name_defval = new KBVar(FString());
	pMonster_name->pDefaultVal = pMonster_name_defval;
	pMonsterModule->propertys.Add(TEXT("name"), pMonster_name); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_name->aliasID, pMonster_name);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(name / 41003).");

	Property* pMonster_state = new Property();
	pMonster_state->name = TEXT("state");
	pMonster_state->properUtype = 47006;
	pMonster_state->properFlags = 4;
	pMonster_state->aliasID = 14;
	KBVar* pMonster_state_defval = new KBVar((int8)FCString::Atoi64(TEXT("0")));
	pMonster_state->pDefaultVal = pMonster_state_defval;
	pMonsterModule->propertys.Add(TEXT("state"), pMonster_state); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_state->aliasID, pMonster_state);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(state / 47006).");

	Property* pMonster_subState = new Property();
	pMonster_subState->name = TEXT("subState");
	pMonster_subState->properUtype = 47007;
	pMonster_subState->properFlags = 4;
	pMonster_subState->aliasID = 15;
	KBVar* pMonster_subState_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pMonster_subState->pDefaultVal = pMonster_subState_defval;
	pMonsterModule->propertys.Add(TEXT("subState"), pMonster_subState); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_subState->aliasID, pMonster_subState);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(subState / 47007).");

	Property* pMonster_uid = new Property();
	pMonster_uid->name = TEXT("uid");
	pMonster_uid->properUtype = 41004;
	pMonster_uid->properFlags = 4;
	pMonster_uid->aliasID = 16;
	KBVar* pMonster_uid_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pMonster_uid->pDefaultVal = pMonster_uid_defval;
	pMonsterModule->propertys.Add(TEXT("uid"), pMonster_uid); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_uid->aliasID, pMonster_uid);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(uid / 41004).");

	Property* pMonster_utype = new Property();
	pMonster_utype->name = TEXT("utype");
	pMonster_utype->properUtype = 41005;
	pMonster_utype->properFlags = 4;
	pMonster_utype->aliasID = 17;
	KBVar* pMonster_utype_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pMonster_utype->pDefaultVal = pMonster_utype_defval;
	pMonsterModule->propertys.Add(TEXT("utype"), pMonster_utype); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_utype->aliasID, pMonster_utype);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(utype / 41005).");

	TArray<DATATYPE_BASE*> Monster_recvDamage_args;
	Monster_recvDamage_args.Add(EntityDef::id2datatypes[8]);
	Monster_recvDamage_args.Add(EntityDef::id2datatypes[8]);
	Monster_recvDamage_args.Add(EntityDef::id2datatypes[8]);
	Monster_recvDamage_args.Add(EntityDef::id2datatypes[8]);

	Method* pMonster_recvDamage = new Method();
	pMonster_recvDamage->name = TEXT("recvDamage");
	pMonster_recvDamage->methodUtype = 34;
	pMonster_recvDamage->aliasID = 1;
	pMonster_recvDamage->args = Monster_recvDamage_args;

	pMonsterModule->methods.Add(TEXT("recvDamage"), pMonster_recvDamage); 
	pMonsterModule->useMethodDescrAlias = true;
	pMonsterModule->idmethods.Add((uint16)pMonster_recvDamage->aliasID, pMonster_recvDamage);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), method(recvDamage / 34).");

	ScriptModule* pNPCModule = new ScriptModule("NPC", 6);
	EntityDef::moduledefs.Add(TEXT("NPC"), pNPCModule);
	EntityDef::idmoduledefs.Add(6, pNPCModule);

	Property* pNPC_position = new Property();
	pNPC_position->name = TEXT("position");
	pNPC_position->properUtype = 40000;
	pNPC_position->properFlags = 4;
	pNPC_position->aliasID = 1;
	KBVar* pNPC_position_defval = new KBVar(FVector());
	pNPC_position->pDefaultVal = pNPC_position_defval;
	pNPCModule->propertys.Add(TEXT("position"), pNPC_position); 

	pNPCModule->usePropertyDescrAlias = true;
	pNPCModule->idpropertys.Add((uint16)pNPC_position->aliasID, pNPC_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(NPC), property(position / 40000).");

	Property* pNPC_direction = new Property();
	pNPC_direction->name = TEXT("direction");
	pNPC_direction->properUtype = 40001;
	pNPC_direction->properFlags = 4;
	pNPC_direction->aliasID = 2;
	KBVar* pNPC_direction_defval = new KBVar(FVector());
	pNPC_direction->pDefaultVal = pNPC_direction_defval;
	pNPCModule->propertys.Add(TEXT("direction"), pNPC_direction); 

	pNPCModule->usePropertyDescrAlias = true;
	pNPCModule->idpropertys.Add((uint16)pNPC_direction->aliasID, pNPC_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(NPC), property(direction / 40001).");

	Property* pNPC_spaceID = new Property();
	pNPC_spaceID->name = TEXT("spaceID");
	pNPC_spaceID->properUtype = 40002;
	pNPC_spaceID->properFlags = 16;
	pNPC_spaceID->aliasID = 3;
	KBVar* pNPC_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pNPC_spaceID->pDefaultVal = pNPC_spaceID_defval;
	pNPCModule->propertys.Add(TEXT("spaceID"), pNPC_spaceID); 

	pNPCModule->usePropertyDescrAlias = true;
	pNPCModule->idpropertys.Add((uint16)pNPC_spaceID->aliasID, pNPC_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(NPC), property(spaceID / 40002).");

	Property* pNPC_entityNO = new Property();
	pNPC_entityNO->name = TEXT("entityNO");
	pNPC_entityNO->properUtype = 51007;
	pNPC_entityNO->properFlags = 4;
	pNPC_entityNO->aliasID = 4;
	KBVar* pNPC_entityNO_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pNPC_entityNO->pDefaultVal = pNPC_entityNO_defval;
	pNPCModule->propertys.Add(TEXT("entityNO"), pNPC_entityNO); 

	pNPCModule->usePropertyDescrAlias = true;
	pNPCModule->idpropertys.Add((uint16)pNPC_entityNO->aliasID, pNPC_entityNO);

	//DEBUG_MSG("EntityDef::initScriptModules: add(NPC), property(entityNO / 51007).");

	Property* pNPC_modelID = new Property();
	pNPC_modelID->name = TEXT("modelID");
	pNPC_modelID->properUtype = 41006;
	pNPC_modelID->properFlags = 4;
	pNPC_modelID->aliasID = 5;
	KBVar* pNPC_modelID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pNPC_modelID->pDefaultVal = pNPC_modelID_defval;
	pNPCModule->propertys.Add(TEXT("modelID"), pNPC_modelID); 

	pNPCModule->usePropertyDescrAlias = true;
	pNPCModule->idpropertys.Add((uint16)pNPC_modelID->aliasID, pNPC_modelID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(NPC), property(modelID / 41006).");

	Property* pNPC_modelScale = new Property();
	pNPC_modelScale->name = TEXT("modelScale");
	pNPC_modelScale->properUtype = 41007;
	pNPC_modelScale->properFlags = 4;
	pNPC_modelScale->aliasID = 6;
	KBVar* pNPC_modelScale_defval = new KBVar((uint8)FCString::Atoi64(TEXT("30")));
	pNPC_modelScale->pDefaultVal = pNPC_modelScale_defval;
	pNPCModule->propertys.Add(TEXT("modelScale"), pNPC_modelScale); 

	pNPCModule->usePropertyDescrAlias = true;
	pNPCModule->idpropertys.Add((uint16)pNPC_modelScale->aliasID, pNPC_modelScale);

	//DEBUG_MSG("EntityDef::initScriptModules: add(NPC), property(modelScale / 41007).");

	Property* pNPC_moveSpeed = new Property();
	pNPC_moveSpeed->name = TEXT("moveSpeed");
	pNPC_moveSpeed->properUtype = 43;
	pNPC_moveSpeed->properFlags = 4;
	pNPC_moveSpeed->aliasID = 7;
	KBVar* pNPC_moveSpeed_defval = new KBVar((uint8)FCString::Atoi64(TEXT("50")));
	pNPC_moveSpeed->pDefaultVal = pNPC_moveSpeed_defval;
	pNPCModule->propertys.Add(TEXT("moveSpeed"), pNPC_moveSpeed); 

	pNPCModule->usePropertyDescrAlias = true;
	pNPCModule->idpropertys.Add((uint16)pNPC_moveSpeed->aliasID, pNPC_moveSpeed);

	//DEBUG_MSG("EntityDef::initScriptModules: add(NPC), property(moveSpeed / 43).");

	Property* pNPC_name = new Property();
	pNPC_name->name = TEXT("name");
	pNPC_name->properUtype = 41003;
	pNPC_name->properFlags = 4;
	pNPC_name->aliasID = 8;
	KBVar* pNPC_name_defval = new KBVar(FString());
	pNPC_name->pDefaultVal = pNPC_name_defval;
	pNPCModule->propertys.Add(TEXT("name"), pNPC_name); 

	pNPCModule->usePropertyDescrAlias = true;
	pNPCModule->idpropertys.Add((uint16)pNPC_name->aliasID, pNPC_name);

	//DEBUG_MSG("EntityDef::initScriptModules: add(NPC), property(name / 41003).");

	Property* pNPC_uid = new Property();
	pNPC_uid->name = TEXT("uid");
	pNPC_uid->properUtype = 41004;
	pNPC_uid->properFlags = 4;
	pNPC_uid->aliasID = 9;
	KBVar* pNPC_uid_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pNPC_uid->pDefaultVal = pNPC_uid_defval;
	pNPCModule->propertys.Add(TEXT("uid"), pNPC_uid); 

	pNPCModule->usePropertyDescrAlias = true;
	pNPCModule->idpropertys.Add((uint16)pNPC_uid->aliasID, pNPC_uid);

	//DEBUG_MSG("EntityDef::initScriptModules: add(NPC), property(uid / 41004).");

	Property* pNPC_utype = new Property();
	pNPC_utype->name = TEXT("utype");
	pNPC_utype->properUtype = 41005;
	pNPC_utype->properFlags = 4;
	pNPC_utype->aliasID = 10;
	KBVar* pNPC_utype_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pNPC_utype->pDefaultVal = pNPC_utype_defval;
	pNPCModule->propertys.Add(TEXT("utype"), pNPC_utype); 

	pNPCModule->usePropertyDescrAlias = true;
	pNPCModule->idpropertys.Add((uint16)pNPC_utype->aliasID, pNPC_utype);

	//DEBUG_MSG("EntityDef::initScriptModules: add(NPC), property(utype / 41005).");

	pNPCModule->useMethodDescrAlias = true;
	ScriptModule* pGateModule = new ScriptModule("Gate", 7);
	EntityDef::moduledefs.Add(TEXT("Gate"), pGateModule);
	EntityDef::idmoduledefs.Add(7, pGateModule);

	Property* pGate_position = new Property();
	pGate_position->name = TEXT("position");
	pGate_position->properUtype = 40000;
	pGate_position->properFlags = 4;
	pGate_position->aliasID = 1;
	KBVar* pGate_position_defval = new KBVar(FVector());
	pGate_position->pDefaultVal = pGate_position_defval;
	pGateModule->propertys.Add(TEXT("position"), pGate_position); 

	pGateModule->usePropertyDescrAlias = true;
	pGateModule->idpropertys.Add((uint16)pGate_position->aliasID, pGate_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Gate), property(position / 40000).");

	Property* pGate_direction = new Property();
	pGate_direction->name = TEXT("direction");
	pGate_direction->properUtype = 40001;
	pGate_direction->properFlags = 4;
	pGate_direction->aliasID = 2;
	KBVar* pGate_direction_defval = new KBVar(FVector());
	pGate_direction->pDefaultVal = pGate_direction_defval;
	pGateModule->propertys.Add(TEXT("direction"), pGate_direction); 

	pGateModule->usePropertyDescrAlias = true;
	pGateModule->idpropertys.Add((uint16)pGate_direction->aliasID, pGate_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Gate), property(direction / 40001).");

	Property* pGate_spaceID = new Property();
	pGate_spaceID->name = TEXT("spaceID");
	pGate_spaceID->properUtype = 40002;
	pGate_spaceID->properFlags = 16;
	pGate_spaceID->aliasID = 3;
	KBVar* pGate_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pGate_spaceID->pDefaultVal = pGate_spaceID_defval;
	pGateModule->propertys.Add(TEXT("spaceID"), pGate_spaceID); 

	pGateModule->usePropertyDescrAlias = true;
	pGateModule->idpropertys.Add((uint16)pGate_spaceID->aliasID, pGate_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Gate), property(spaceID / 40002).");

	Property* pGate_entityNO = new Property();
	pGate_entityNO->name = TEXT("entityNO");
	pGate_entityNO->properUtype = 51007;
	pGate_entityNO->properFlags = 4;
	pGate_entityNO->aliasID = 4;
	KBVar* pGate_entityNO_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pGate_entityNO->pDefaultVal = pGate_entityNO_defval;
	pGateModule->propertys.Add(TEXT("entityNO"), pGate_entityNO); 

	pGateModule->usePropertyDescrAlias = true;
	pGateModule->idpropertys.Add((uint16)pGate_entityNO->aliasID, pGate_entityNO);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Gate), property(entityNO / 51007).");

	Property* pGate_modelID = new Property();
	pGate_modelID->name = TEXT("modelID");
	pGate_modelID->properUtype = 41006;
	pGate_modelID->properFlags = 4;
	pGate_modelID->aliasID = 5;
	KBVar* pGate_modelID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pGate_modelID->pDefaultVal = pGate_modelID_defval;
	pGateModule->propertys.Add(TEXT("modelID"), pGate_modelID); 

	pGateModule->usePropertyDescrAlias = true;
	pGateModule->idpropertys.Add((uint16)pGate_modelID->aliasID, pGate_modelID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Gate), property(modelID / 41006).");

	Property* pGate_modelScale = new Property();
	pGate_modelScale->name = TEXT("modelScale");
	pGate_modelScale->properUtype = 41007;
	pGate_modelScale->properFlags = 4;
	pGate_modelScale->aliasID = 6;
	KBVar* pGate_modelScale_defval = new KBVar((uint8)FCString::Atoi64(TEXT("30")));
	pGate_modelScale->pDefaultVal = pGate_modelScale_defval;
	pGateModule->propertys.Add(TEXT("modelScale"), pGate_modelScale); 

	pGateModule->usePropertyDescrAlias = true;
	pGateModule->idpropertys.Add((uint16)pGate_modelScale->aliasID, pGate_modelScale);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Gate), property(modelScale / 41007).");

	Property* pGate_name = new Property();
	pGate_name->name = TEXT("name");
	pGate_name->properUtype = 41003;
	pGate_name->properFlags = 4;
	pGate_name->aliasID = 7;
	KBVar* pGate_name_defval = new KBVar(FString());
	pGate_name->pDefaultVal = pGate_name_defval;
	pGateModule->propertys.Add(TEXT("name"), pGate_name); 

	pGateModule->usePropertyDescrAlias = true;
	pGateModule->idpropertys.Add((uint16)pGate_name->aliasID, pGate_name);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Gate), property(name / 41003).");

	Property* pGate_uid = new Property();
	pGate_uid->name = TEXT("uid");
	pGate_uid->properUtype = 41004;
	pGate_uid->properFlags = 4;
	pGate_uid->aliasID = 8;
	KBVar* pGate_uid_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pGate_uid->pDefaultVal = pGate_uid_defval;
	pGateModule->propertys.Add(TEXT("uid"), pGate_uid); 

	pGateModule->usePropertyDescrAlias = true;
	pGateModule->idpropertys.Add((uint16)pGate_uid->aliasID, pGate_uid);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Gate), property(uid / 41004).");

	Property* pGate_utype = new Property();
	pGate_utype->name = TEXT("utype");
	pGate_utype->properUtype = 41005;
	pGate_utype->properFlags = 4;
	pGate_utype->aliasID = 9;
	KBVar* pGate_utype_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pGate_utype->pDefaultVal = pGate_utype_defval;
	pGateModule->propertys.Add(TEXT("utype"), pGate_utype); 

	pGateModule->usePropertyDescrAlias = true;
	pGateModule->idpropertys.Add((uint16)pGate_utype->aliasID, pGate_utype);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Gate), property(utype / 41005).");

	pGateModule->useMethodDescrAlias = true;
}

void EntityDef::initDefTypes()
{
	{
		uint16 utype = 2;
		FString typeName = TEXT("ENTITY_SUBSTATE");
		FString name = TEXT("UINT8");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 3;
		FString typeName = TEXT("UINT16");
		FString name = TEXT("UINT16");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 5;
		FString typeName = TEXT("UID");
		FString name = TEXT("UINT64");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 4;
		FString typeName = TEXT("ENTITY_UTYPE");
		FString name = TEXT("UINT32");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 6;
		FString typeName = TEXT("ENTITY_STATE");
		FString name = TEXT("INT8");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 7;
		FString typeName = TEXT("INT16");
		FString name = TEXT("INT16");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 8;
		FString typeName = TEXT("ENTITY_FORBIDS");
		FString name = TEXT("INT32");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 9;
		FString typeName = TEXT("INT64");
		FString name = TEXT("INT64");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 1;
		FString typeName = TEXT("STRING");
		FString name = TEXT("STRING");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 12;
		FString typeName = TEXT("UNICODE");
		FString name = TEXT("UNICODE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 13;
		FString typeName = TEXT("FLOAT");
		FString name = TEXT("FLOAT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 14;
		FString typeName = TEXT("DOUBLE");
		FString name = TEXT("DOUBLE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("UID1");
		FString name = TEXT("PYTHON");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_DICT");
		FString name = TEXT("PY_DICT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_TUPLE");
		FString name = TEXT("PY_TUPLE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_LIST");
		FString name = TEXT("PY_LIST");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 20;
		FString typeName = TEXT("ENTITYCALL");
		FString name = TEXT("ENTITYCALL");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 11;
		FString typeName = TEXT("BLOB");
		FString name = TEXT("BLOB");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 15;
		FString typeName = TEXT("VECTOR2");
		FString name = TEXT("VECTOR2");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 16;
		FString typeName = TEXT("DIRECTION3D");
		FString name = TEXT("VECTOR3");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 17;
		FString typeName = TEXT("VECTOR4");
		FString name = TEXT("VECTOR4");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 22;
		FString typeName = TEXT("ENTITY_FORBID_COUNTER");
		DATATYPE_ENTITY_FORBID_COUNTER* pDatatype = new DATATYPE_ENTITY_FORBID_COUNTER();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 23;
		FString typeName = TEXT("ENTITYID_LIST");
		DATATYPE_ENTITYID_LIST* pDatatype = new DATATYPE_ENTITYID_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 24;
		FString typeName = TEXT("AVATAR_DATA");
		DATATYPE_AVATAR_DATA* pDatatype = new DATATYPE_AVATAR_DATA();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 25;
		FString typeName = TEXT("AVATAR_INFOS");
		DATATYPE_AVATAR_INFOS* pDatatype = new DATATYPE_AVATAR_INFOS();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 26;
		FString typeName = TEXT("AVATAR_INFOS_LIST");
		DATATYPE_AVATAR_INFOS_LIST* pDatatype = new DATATYPE_AVATAR_INFOS_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 28;
		FString typeName = TEXT("BAG");
		DATATYPE_BAG* pDatatype = new DATATYPE_BAG();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 31;
		FString typeName = TEXT("EXAMPLES");
		DATATYPE_EXAMPLES* pDatatype = new DATATYPE_EXAMPLES();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 32;
		FString typeName = TEXT("AnonymousArray_32");
		DATATYPE_AnonymousArray_32* pDatatype = new DATATYPE_AnonymousArray_32();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 33;
		FString typeName = TEXT("AnonymousArray_33");
		FString name = TEXT("ENTITY_COMPONENT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 34;
		FString typeName = TEXT("AnonymousArray_34");
		FString name = TEXT("ENTITY_COMPONENT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 35;
		FString typeName = TEXT("AnonymousArray_35");
		FString name = TEXT("ENTITY_COMPONENT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	for(auto& Elem : EntityDef::datatypes)
	{
		if(Elem.Value)
		{
			Elem.Value->bind();
		}
	}
}


}