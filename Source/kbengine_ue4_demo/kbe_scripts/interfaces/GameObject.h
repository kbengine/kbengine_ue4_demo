// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

class Entity;

/*
	对应entity_defs/interfaces/*
*/
class GameObject : public Entity
{
public:
	GameObject();
	virtual ~GameObject();

	void set_name(FString old);
	void set_modelID(uint32 old);
	void set_modelScale(uint8 old);

public:
	// def中定义的客户端涉及属性和方法都需要包含在ENTITYDEF_BEGIN和ENTITYDEF_END之间
	ENTITYDEF_BEGIN()
	FString name; // 由于与底层某些名称冲突，所以这里使用了一个别名防止冲突
	uint32 uid;
	uint32 utype;
	uint32 modelID;
	uint8 modelScale;
	ENTITYDEF_END()
};
