// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Object.h"
#include "KBECommon.h"
#include "KBEvent.generated.h"


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
UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const
	{
		return KEventDataTypes::UNKNOWN;
	}
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
		static bool registerEvent(const FString& eventName, const FString& funcName, TFunction<void(const UKBEventData*)> func, void* objPtr);
		static bool deregister(void* objPtr, const FString& eventName, const FString& funcName);
		static bool deregister(void* objPtr);

		static void fire(const FString& eventName, UKBEventData* pEventData);

		static void clear();
		static void clearFiredEvents();

protected:
	struct EventObj
	{
		TFunction<void(const UKBEventData*)> method;
		FString funcName;
		void* objPtr;
	};

	static TMap<FString, TArray<EventObj>> events_;
};


// 注册事件
#define KBENGINE_REGISTER_EVENT(EVENT_NAME, EVENT_FUNC) \
	KBEvent::registerEvent(EVENT_NAME, #EVENT_FUNC, [this](const UKBEventData* pEventData) {	EVENT_FUNC(pEventData);	}, (void*)this);

// 注册事件，可重写事件函数
#define KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC(EVENT_NAME, FUNC_NAME, EVENT_FUNC) \
	KBEvent::registerEvent(EVENT_NAME, FUNC_NAME, EVENT_FUNC, (void*)this);

// 注销这个对象某个事件
#define KBENGINE_DEREGISTER_EVENT(EVENT_NAME) KBEvent::deregister((void*)this, EVENT_NAME, FUNC_NAME);

// 注销这个对象所有的事件
#define KBENGINE_DEREGISTER_ALL_EVENT()	KBEvent::deregister((void*)this);

// fire event
#define KBENGINE_EVENT_FIRE(EVENT_NAME, EVENT_DATA) KBEvent::fire(EVENT_NAME, EVENT_DATA);

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_Baseapp_importClientMessages : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::Baseapp_importClientMessages;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onKicked : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onKicked;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 failedcode;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_createAccount : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::createAccount;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString password;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	TArray<uint8> datas;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_login : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::login;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString password;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	TArray<uint8> datas;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onLoginFailed : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onLoginFailed;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 failedcode;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onLoginBaseapp : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onLoginBaseapp;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onLoginSuccessfully : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onLoginSuccessfully;
	}

	UPROPERTY(EditAnywhere, /*BlueprintReadWrite, No support*/ Category = KBEngine)
	uint64  entity_uuid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 entity_id;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onReLoginBaseapp : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
		virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onReLoginBaseapp;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onLoginBaseappFailed : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onLoginBaseappFailed;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 failedcode;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onReLoginBaseappFailed : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onReLoginBaseappFailed;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 failedcode;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onReLoginBaseappSuccessfully : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onReLoginBaseappSuccessfully;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onVersionNotMatch : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onVersionNotMatch;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString clientVersion;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString serverVersion;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onScriptVersionNotMatch : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onScriptVersionNotMatch;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString clientScriptVersion;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString serverScriptVersion;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_Loginapp_importClientMessages : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::Loginapp_importClientMessages;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_Baseapp_importClientEntityDef : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::Baseapp_importClientEntityDef;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onControlled : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onControlled;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onLoseControlledEntity : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onLoseControlledEntity;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_updatePosition : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::updatePosition;
	}

	FVector position;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_set_position : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::set_position;
	}

	FVector position;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_set_direction : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
		virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::set_direction;
	}

	FRotator direction;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onCreateAccountResult : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onCreateAccountResult;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_addSpaceGeometryMapping : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::addSpaceGeometryMapping;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onSetSpaceData : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onSetSpaceData;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onDelSpaceData : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onDelSpaceData;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onDisableConnect : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onDisableConnect;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onConnectStatus : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onConnectStatus;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	bool success;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onEnterWorld : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onEnterWorld;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onLeaveWorld : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onLeaveWorld;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onEnterSpace : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onEnterSpace;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onLeaveSpace : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onLeaveSpace;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onAvatarEnterWorld : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::onAvatarEnterWorld;
	}
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_resetPassword : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::resetPassword;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString username;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_bindAccountEmail : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::bindAccountEmail;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString email;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_newPassword : public UKBEventData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	virtual KEventDataTypes getType() const override
	{
		return KEventDataTypes::newPassword;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString old_password;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString new_password;
};
