// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

class Entity;

/*
	KBEngine逻辑层的实体基础类
	所有扩展出的游戏实体都应该继承于该模块
*/
class Combat
{
public:
	Combat();
	virtual ~Combat();

	void set_HP(int32 old);
	void set_HP_Max(int32 old);
	void set_MP(int32 old);
	void set_MP_Max(int32 old);

public:
	// def中定义的客户端涉及属性
	int32 HP;
	int32 HP_Max;
	int32 MP;
	int32 MP_Max;
};
