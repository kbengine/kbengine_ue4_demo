// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "KBECommon.h"

class GameObject;

/*
	KBEngine逻辑层的实体基础类
	所有扩展出的游戏实体都应该继承于该模块
*/
class Account : public GameObject
{
public:
	Account();
	virtual ~Account();

public:
	virtual void __init__() override;
	virtual void onDestroy() override;

	void reqCreateAvatar(uint8 roleType, const FString& name);
	void reqRemoveAvatar(const FString& name);
	void reqRemoveAvatar(uint64 dbid);

	void onReqAvatarList(const KB_ARRAY& datas);

	struct AVATAR_DATA
	{
		int8 param1;
		TArray<uint8> param2;
	};

	struct AVATAR_INFOS
	{
		uint64 dbid;
		FString name;
		uint8 roleType;
		uint16 level;
		AVATAR_DATA data;
	};

	// def中定义的客户端涉及属性
	AVATAR_INFOS characters;
	DBID lastSelCharacter;
};
