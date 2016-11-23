// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

class Entity;

/*
	KBEngine逻辑层的实体基础类
	所有扩展出的游戏实体都应该继承于该模块
*/
class GameObject : public Entity
{
public:
	GameObject();
	virtual ~GameObject();

public:
	// def中定义的客户端涉及属性
	FString name_; // 由于与底层某些名称冲突，所以这里使用了一个别名防止冲突
	uint32 uid;
	uint32 utype;
	uint32 modelID;
	uint8 modelScale;
};
