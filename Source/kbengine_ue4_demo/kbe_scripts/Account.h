// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

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

	void set_spaceID(uint32 oldVal) {

	}

	uint32 spaceID;
};
