// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "KBECommon.h"

#include "interfaces/GameObject.h"

/*
	对应entity_defs/

	要实现一个KBE对应的实体必须经过以下几步
	1: 在服务器entity_defs中entities.xml中注册实体并实现实体的def定义
	2: 在服务器的相关位置如：assets/scripts目录的cell（ 取决于实体拥有该部分）或base（ 取决于实体拥有该部分）文件夹下实现实体的服务器部分py脚本模块
	3: 在UE4客户端中kbe_scripts文件夹下实现实体的客户端部分脚本模块（这里统一称为实体脚本，虽然是C++实现），UE4实现实体后必须有如下几步
		A：在实体的头文件中按照格式定义ENTITYDEF_DECLARE_模块名， 具体看demo
		B：在实体CPP文件中ENTITYDEF_CLASS_REGISTER将实体注册，具体看demo
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
	void reqRemoveAvatar(uint64 dbid);
	void selectAvatarGame(uint64 dbid);

	void onReqAvatarList(const KB_FIXED_DICT& datas);
	void onCreateAvatarResult(uint8 retcode, const KB_FIXED_DICT& info);
	void onRemoveAvatar(uint64 dbid);

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

	TMap<uint64, AVATAR_INFOS> characters;

	// def中定义的客户端涉及属性
	DBID lastSelCharacter;
};

/*
Declare all of the properties and methods of the KBE-Entity

Example:
	#define ENTITYDEF_DECLARE_[module name of Entity](PARENT_MODULE)	\
		ENTITYDEF_PROPERTY_*(PARENT_MODULE, xx_property)	\
		ENTITYDEF_METHOD_ARGS[0~20]_REGISTER(PARENT_MODULE, xx_method)
*/

#define ENTITYDEF_DECLARE_Account(PARENT_MODULE)	\
	ENTITYDEF_PROPERTY_REGISTER(PARENT_MODULE, lastSelCharacter)	\
	ENTITYDEF_METHOD_ARGS1_REGISTER(PARENT_MODULE, onReqAvatarList)	\
	ENTITYDEF_METHOD_ARGS1_REGISTER(PARENT_MODULE, onRemoveAvatar)	\
	ENTITYDEF_METHOD_ARGS2_REGISTER(PARENT_MODULE, onCreateAvatarResult)
