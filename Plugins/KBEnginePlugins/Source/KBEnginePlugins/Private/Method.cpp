
#include "KBEnginePluginsPrivatePCH.h"
#include "DataTypes.h"
#include "Method.h"

Method::Method():
	name(TEXT("")),
	methodUtype(0),
	aliasID(-1),
	args(),
	pEntityDefMethodHandle(NULL)
{
}

Method::~Method()
{
	SAFE_RELEASE(pEntityDefMethodHandle);
}
