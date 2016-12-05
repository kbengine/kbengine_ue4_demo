// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "KBECommon.h"
#include "KBEvent.h"
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
class KBENGINE_UE4_DEMO_API UKBEventData_reqCreateAvatar : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	uint8 roleType;

	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	FString name;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINE_UE4_DEMO_API UKBEventData_onReqAvatarList : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	TArray<FAVATAR_INFOS> avatars;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINE_UE4_DEMO_API UKBEventData_reqRemoveAvatar : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	FAVATAR_INFOS avatarInfos;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINE_UE4_DEMO_API UKBEventData_onRemoveAvatar : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	FAVATAR_INFOS avatarInfos;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINE_UE4_DEMO_API UKBEventData_onCreateAvatarResult : public UKBEventData
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
class KBENGINE_UE4_DEMO_API UKBEventData_selectAvatarGame : public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = KBEngine, BlueprintReadWrite, EditAnywhere)
	FAVATAR_INFOS avatarInfos;
};
