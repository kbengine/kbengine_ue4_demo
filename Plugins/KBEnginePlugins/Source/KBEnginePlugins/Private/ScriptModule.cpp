
#include "KBEnginePluginsPrivatePCH.h"
#include "ScriptModule.h"
#include "Method.h"
#include "Property.h"
#include "Entity.h"

ScriptModule::ScriptModule(const FString& moduleName):
	name(moduleName),
	usePropertyDescrAlias(false),
	useMethodDescrAlias(false),
	propertys(),
	idpropertys(),
	methods(),
	base_methods(),
	cell_methods(),
	idmethods(),
	idbase_methods(),
	idcell_methods(),
	pEntityCreator(NULL)
{
	pEntityCreator = EntityFactory::findCreator(moduleName);
	if (!pEntityCreator)
		ERROR_MSG("can't load scriptSodule(KBEngine.%s)!", *moduleName);
}

ScriptModule::~ScriptModule()
{
}
