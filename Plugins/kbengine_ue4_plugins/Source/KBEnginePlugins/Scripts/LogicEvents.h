// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/KBECommon.h"
#include "Engine/KBEvent.h"
#include "LogicEvents.generated.h"

/**
	所有由逻辑层产生的事件都在这里定义
*/

USTRUCT(BlueprintType)
struct FAVATAR_INFOS
{
	GENERATED_BODY()

	UPROPERTY(Category = KBEngine, EditAnywhere)
	uint64 dbid;

	// 由于蓝图不可读取uint64类型， 因此提供一个字符串类型用于比较和读取
	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	FString sdbid;

	void set(DBID _dbid, const FString& _name, uint8 _roleType, int _level, bool _lastSelCharacter)
	{
		name = _name;
		dbid = _dbid;
		sdbid = FString::Printf(TEXT("%lld"), dbid);
		roleType = _roleType;
		level = _level;
		lastSelCharacter = _lastSelCharacter;
	}

	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	FString name;

	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	uint8 roleType;

	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	int level;

	// 服务端记录的最后一次所选择的角色
	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	bool lastSelCharacter;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqCreateAvatar : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	uint8 roleType;

	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	FString name;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onReqAvatarList : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	TArray<FAVATAR_INFOS> avatars;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqRemoveAvatar : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	FAVATAR_INFOS avatarInfos;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onRemoveAvatar : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	FAVATAR_INFOS avatarInfos;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_onCreateAvatarResult : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	int errorCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FString errorStr;

	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	FAVATAR_INFOS avatarInfos;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_selectAvatarGame : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	FAVATAR_INFOS avatarInfos;
};


UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_set_moveSpeed : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;

	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	float moveSpeed;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_set_entityNO : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;

	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	int32 entityNO;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_set_name : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;

	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	FString name;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_set_modelID : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = KBEngine)
	uint32 modelID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_set_modelScale : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	uint8 modelScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_set_HP : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_set_HP_Max : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 HP_Max;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_set_MP : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_MP_Max : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 MP_Max;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;
};




UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_set_flags : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 flags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_set_state : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 state;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_set_subState : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 subState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_set_forbids : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 forbids;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqRelive : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	uint8 reliveType;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_recvDamage : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 attackerID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 skillID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 damageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int32 damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;
};