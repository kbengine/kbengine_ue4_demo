// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.



#include "KBECommon.h"
#include "NetworkInterfaceDef.h"


NETWORK_INTERFACE_DECLARE_BEGIN(KBEngineApp)
	NETWORK_MESSAGE_HANDLER_STREAM(Client_onHelloCB,									NETWORK_VARIABLE_MESSAGE)

	NETWORK_MESSAGE_HANDLER_STREAM(Client_onScriptVersionNotMatch,						NETWORK_VARIABLE_MESSAGE)

	NETWORK_MESSAGE_HANDLER_STREAM(Client_onVersionNotMatch,							NETWORK_VARIABLE_MESSAGE)

	NETWORK_MESSAGE_HANDLER_STREAM(Client_onImportClientMessages,						NETWORK_VARIABLE_MESSAGE)

	NETWORK_MESSAGE_HANDLER_STREAM(Client_onImportServerErrorsDescr,					NETWORK_VARIABLE_MESSAGE)
	
	NETWORK_MESSAGE_HANDLER_ARGS0(Client_onAppActiveTickCB,								NETWORK_FIXED_MESSAGE)

	NETWORK_MESSAGE_HANDLER_STREAM(Client_onLoginFailed,								NETWORK_VARIABLE_MESSAGE)

	NETWORK_MESSAGE_HANDLER_ARGS1(Client_onLoginBaseappFailed,							NETWORK_FIXED_MESSAGE,
									uint16,												failedcode)

	NETWORK_MESSAGE_HANDLER_ARGS1(Client_onReLoginBaseappFailed,						NETWORK_FIXED_MESSAGE,
									uint16,												failedcode)

	NETWORK_MESSAGE_HANDLER_STREAM(Client_onReLoginBaseappSuccessfully,					NETWORK_VARIABLE_MESSAGE)
	
	NETWORK_MESSAGE_HANDLER_STREAM(Client_onLoginSuccessfully,							NETWORK_VARIABLE_MESSAGE)

	NETWORK_MESSAGE_HANDLER_STREAM(Client_onImportClientEntityDef,						NETWORK_VARIABLE_MESSAGE)
	
	NETWORK_MESSAGE_HANDLER_ARGS1(Client_onKicked,										NETWORK_FIXED_MESSAGE,
									uint16,												failedcode)

	NETWORK_MESSAGE_HANDLER_ARGS1(Client_onEntityDestroyed,								NETWORK_FIXED_MESSAGE,
									int32,												eid)

	NETWORK_MESSAGE_HANDLER_ARGS3(Client_onCreatedProxies,								NETWORK_VARIABLE_MESSAGE,
									uint64,												rndUUID,
									int32,												eid,
									FString,											entityType)

	NETWORK_MESSAGE_HANDLER_STREAM(Client_onUpdatePropertysOptimized,					NETWORK_VARIABLE_MESSAGE)

	NETWORK_MESSAGE_HANDLER_STREAM(Client_onUpdatePropertys,							NETWORK_VARIABLE_MESSAGE)

NETWORK_INTERFACE_DECLARE_END()
