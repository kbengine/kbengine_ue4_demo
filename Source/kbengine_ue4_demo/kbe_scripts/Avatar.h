// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "KBECommon.h"

class GameObject;

/*
	KBEngine逻辑层的实体基础类
	所有扩展出的游戏实体都应该继承于该模块
*/
class Avatar : public GameObject
{
public:
	Avatar();
	virtual ~Avatar();

public:
	// def中定义的客户端涉及属性
	uint16 level;
	uint16 own_val;
};
