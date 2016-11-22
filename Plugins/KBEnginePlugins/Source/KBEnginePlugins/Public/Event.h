// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KBECommon.h"
#include "Event.generated.h"


UENUM(BlueprintType)
enum class KEventDataTypes : uint8
{
	UNKNOWN										UMETA(DisplayName = "unknown"),
	Baseapp_importClientMessages				UMETA(DisplayName = "Baseapp_importClientMessages"),
	onKicked									UMETA(DisplayName = "onKicked"),
	createAccount								UMETA(DisplayName = "createAccount"),
	login										UMETA(DisplayName = "login"),
	onLoginFailed								UMETA(DisplayName = "onLoginFailed"),
	onLoginBaseapp								UMETA(DisplayName = "onLoginBaseapp"),
	onLoginSuccessfully							UMETA(DisplayName = "onLoginSuccessfully"),
	onReLoginBaseapp							UMETA(DisplayName = "onReLoginBaseapp"),
	onLoginBaseappFailed						UMETA(DisplayName = "onLoginBaseappFailed"),
	onReLoginBaseappFailed						UMETA(DisplayName = "onReLoginBaseappFailed"),
	onReLoginBaseappSuccessfully				UMETA(DisplayName = "onReLoginBaseappSuccessfully"),
	onVersionNotMatch							UMETA(DisplayName = "onVersionNotMatch"),
	onScriptVersionNotMatch						UMETA(DisplayName = "onScriptVersionNotMatch"),
	Loginapp_importClientMessages				UMETA(DisplayName = "Loginapp_importClientMessages"),
	Baseapp_importClientEntityDef				UMETA(DisplayName = "Baseapp_importClientEntityDef"),
	onControlled								UMETA(DisplayName = "onControlled"),
	onLoseControlledEntity						UMETA(DisplayName = "onLoseControlledEntity"),
	updatePosition								UMETA(DisplayName = "updatePosition"),
	set_position								UMETA(DisplayName = "set_position"),
	set_direction								UMETA(DisplayName = "set_direction"),
	onCreateAccountResult						UMETA(DisplayName = "onCreateAccountResult"),
	addSpaceGeometryMapping						UMETA(DisplayName = "addSpaceGeometryMapping"),
	onSetSpaceData								UMETA(DisplayName = "onSetSpaceData"),
	onDelSpaceData								UMETA(DisplayName = "onDelSpaceData"),
	onDisableConnect							UMETA(DisplayName = "onDisableConnect"),
	onConnectStatus								UMETA(DisplayName = "onConnectStatus"),
	onEnterWorld								UMETA(DisplayName = "onEnterWorld"),
	onLeaveWorld								UMETA(DisplayName = "onLeaveWorld"),
	onEnterSpace								UMETA(DisplayName = "onEnterSpace"),
	onLeaveSpace								UMETA(DisplayName = "onLeaveSpace"),
	onAvatarEnterWorld							UMETA(DisplayName = "onAvatarEnterWorld"),
	resetPassword								UMETA(DisplayName = "resetPassword"),
	bindAccountEmail							UMETA(DisplayName = "bindAccountEmail"),
	newPassword									UMETA(DisplayName = "newPassword"),
};

/*
事件模块
事件的数据基础类， 不同事件需要实现不同的数据类
*/
USTRUCT(BlueprintType)
struct FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData(KEventDataTypes t):
	type(t)
	{

	}

	FKEventData() :
	type(KEventDataTypes::UNKNOWN)
	{

	}

	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	KEventDataTypes type;
};

/*
	事件模块
	KBEngine插件层与Unity3D表现层通过事件来交互
*/
class KBENGINEPLUGINS_API KBEvent
{
public:
	KBEvent();
	virtual ~KBEvent();
	
public:
		static bool registerEvent(const FString& eventName, const FString& funcName, TFunction<void(const FKEventData&)> func, void* objPtr);
		static bool deregister(void* objPtr, const FString& eventName, const FString& funcName);
		static bool deregister(void* objPtr);

		static void fire(const FString& eventName, const FKEventData& eventData);

protected:
	struct EventObj
	{
		TFunction<void(const FKEventData&)> method;
		FString funcName;
		void* objPtr;
	};

	static TMap<FString, TArray<EventObj>> events_;
};


// 注册事件
#define KBENGINE_REGISTER_EVENT(EVENT_NAME, EVENT_FUNC) \
	KBEvent::registerEvent(EVENT_NAME, #EVENT_FUNC, [this](const FKEventData& eventData) {	EVENT_FUNC(eventData);	}, (void*)this);

// 注册事件，可重写事件函数
#define KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC(EVENT_NAME, FUNC_NAME, EVENT_FUNC) \
	KBEvent::registerEvent(EVENT_NAME, FUNC_NAME, EVENT_FUNC, (void*)this);

// 注销这个对象某个事件
#define KBENGINE_DEREGISTER_EVENT(EVENT_NAME) KBEvent::deregister((void*)this, EVENT_NAME, FUNC_NAME);

// 注销这个对象所有的事件
#define KBENGINE_DEREGISTER_ALL_EVENT()	KBEvent::deregister((void*)this);

// fire event
#define KBENGINE_EVENT_FIRE(EVENT_NAME, EVENT_DATA) KBEvent::fire(EVENT_NAME, EVENT_DATA);

USTRUCT(BlueprintType)
struct FKEventData_Baseapp_importClientMessages : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_Baseapp_importClientMessages():
	FKEventData(KEventDataTypes::Baseapp_importClientMessages)
	{

	}
};

USTRUCT(BlueprintType)
struct FKEventData_onKicked : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onKicked() :
	FKEventData(KEventDataTypes::onKicked)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 failedcode;
};

USTRUCT(BlueprintType)
struct FKEventData_createAccount : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_createAccount() :
	FKEventData(KEventDataTypes::createAccount)
	{

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString password;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	TArray<uint8> datas;
};

USTRUCT(BlueprintType)
struct FKEventData_login : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_login() :
	FKEventData(KEventDataTypes::login)
	{

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString password;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	TArray<uint8> datas;
};

USTRUCT(BlueprintType)
struct FKEventData_onLoginFailed : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onLoginFailed() :
	FKEventData(KEventDataTypes::onLoginFailed)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 failedcode;
};

USTRUCT(BlueprintType)
struct FKEventData_onLoginBaseapp : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onLoginBaseapp() :
	FKEventData(KEventDataTypes::onLoginBaseapp)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_onLoginSuccessfully : public FKEventData
{
	GENERATED_USTRUCT_BODY()

		FKEventData_onLoginSuccessfully() :
		FKEventData(KEventDataTypes::onLoginSuccessfully)
	{
	}

	UPROPERTY(EditAnywhere, /*BlueprintReadWrite, No support*/ Category = KBEngine)
	uint64  entity_uuid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 entity_id;
};

USTRUCT(BlueprintType)
struct FKEventData_onReLoginBaseapp : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onReLoginBaseapp() :
	FKEventData(KEventDataTypes::onReLoginBaseapp)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_onLoginBaseappFailed : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onLoginBaseappFailed() :
	FKEventData(KEventDataTypes::onLoginBaseappFailed)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 failedcode;
};

USTRUCT(BlueprintType)
struct FKEventData_onReLoginBaseappFailed : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onReLoginBaseappFailed() :
	FKEventData(KEventDataTypes::onReLoginBaseappFailed)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 failedcode;
};

USTRUCT(BlueprintType)
struct FKEventData_onReLoginBaseappSuccessfully : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onReLoginBaseappSuccessfully() :
	FKEventData(KEventDataTypes::onReLoginBaseappSuccessfully)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_onVersionNotMatch : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onVersionNotMatch() :
	FKEventData(KEventDataTypes::onVersionNotMatch)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString clientVersion;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString serverVersion;
};

USTRUCT(BlueprintType)
struct FKEventData_onScriptVersionNotMatch : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onScriptVersionNotMatch() :
	FKEventData(KEventDataTypes::onScriptVersionNotMatch)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString clientScriptVersion;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString serverScriptVersion;
};

USTRUCT(BlueprintType)
struct FKEventData_Loginapp_importClientMessages : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_Loginapp_importClientMessages() :
	FKEventData(KEventDataTypes::Loginapp_importClientMessages)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_Baseapp_importClientEntityDef : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_Baseapp_importClientEntityDef() :
	FKEventData(KEventDataTypes::Baseapp_importClientEntityDef)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_onControlled : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onControlled() :
	FKEventData(KEventDataTypes::onControlled)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_onLoseControlledEntity : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onLoseControlledEntity() :
	FKEventData(KEventDataTypes::onLoseControlledEntity)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_updatePosition : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_updatePosition() :
	FKEventData(KEventDataTypes::updatePosition),
	position()
	{
	}

	FKEventData_updatePosition(const FVector& v) :
	FKEventData(KEventDataTypes::updatePosition),
	position(v)
	{
	}

	FVector position;
};

USTRUCT(BlueprintType)
struct FKEventData_set_position : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_set_position() :
	FKEventData(KEventDataTypes::set_position),
	position()
	{
	}

	FKEventData_set_position(const FVector& v) :
	FKEventData(KEventDataTypes::set_position),
	position(v)
	{
	}

	FVector position;
};

USTRUCT(BlueprintType)
struct FKEventData_set_direction : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_set_direction() :
	FKEventData(KEventDataTypes::set_direction),
	direction()
	{
	}

	FKEventData_set_direction(const FRotator& v) :
	FKEventData(KEventDataTypes::set_direction),
	direction(v)
	{
	}

	FRotator direction;
};

USTRUCT(BlueprintType)
struct FKEventData_onCreateAccountResult : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onCreateAccountResult() :
	FKEventData(KEventDataTypes::onCreateAccountResult)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_addSpaceGeometryMapping : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_addSpaceGeometryMapping() :
	FKEventData(KEventDataTypes::addSpaceGeometryMapping)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_onSetSpaceData : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onSetSpaceData() :
	FKEventData(KEventDataTypes::onSetSpaceData)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_onDelSpaceData : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onDelSpaceData() :
	FKEventData(KEventDataTypes::onDelSpaceData)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_onDisableConnect : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onDisableConnect() :
	FKEventData(KEventDataTypes::onDisableConnect)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_onConnectStatus : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onConnectStatus() :
	FKEventData(KEventDataTypes::onConnectStatus),
	success(false)
	{
	}

	FKEventData_onConnectStatus(bool v) :
	FKEventData(KEventDataTypes::onConnectStatus),
	success(v)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	bool success;
};

USTRUCT(BlueprintType)
struct FKEventData_onEnterWorld : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onEnterWorld() :
	FKEventData(KEventDataTypes::onEnterWorld)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_onLeaveWorld : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onLeaveWorld() :
	FKEventData(KEventDataTypes::onLeaveWorld)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_onEnterSpace : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onEnterSpace() :
	FKEventData(KEventDataTypes::onEnterSpace)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_onLeaveSpace : public FKEventData
{
	GENERATED_USTRUCT_BODY()

		FKEventData_onLeaveSpace() :
		FKEventData(KEventDataTypes::onLeaveSpace)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_onAvatarEnterWorld : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_onAvatarEnterWorld() :
	FKEventData(KEventDataTypes::onAvatarEnterWorld)
	{
	}
};

USTRUCT(BlueprintType)
struct FKEventData_resetPassword : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_resetPassword() :
	FKEventData(KEventDataTypes::resetPassword)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString username;
};

USTRUCT(BlueprintType)
struct FKEventData_bindAccountEmail : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_bindAccountEmail() :
	FKEventData(KEventDataTypes::bindAccountEmail)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString email;
};

USTRUCT(BlueprintType)
struct FKEventData_newPassword : public FKEventData
{
	GENERATED_USTRUCT_BODY()

	FKEventData_newPassword() :
	FKEventData(KEventDataTypes::newPassword)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString old_password;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString new_password;
};
