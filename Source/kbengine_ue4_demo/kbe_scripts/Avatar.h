// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "KBECommon.h"

class GameObject;
class Combat;
class Motion;
class State;
class Flags;
class Spell;
class SkillBox;
class Teleport;
class AvatarLingGen;

/*
	��Ӧentity_defs/

	Ҫʵ��һ��KBE��Ӧ��ʵ����뾭�����¼���
	1: �ڷ�����entity_defs��entities.xml��ע��ʵ�岢ʵ��ʵ���def����
	2: �ڷ����������λ���磺assets/scriptsĿ¼��cell�� ȡ����ʵ��ӵ�иò��֣���base�� ȡ����ʵ��ӵ�иò��֣��ļ�����ʵ��ʵ��ķ���������py�ű�ģ��
	3: ��UE4�ͻ�����kbe_scripts�ļ�����ʵ��ʵ��Ŀͻ��˲��ֽű�ģ�飨����ͳһ��Ϊʵ��ű�����Ȼ��C++ʵ�֣���UE4ʵ��ʵ�����������¼���
		A����ʵ���ͷ�ļ��а��ո�ʽ����ENTITYDEF_DECLARE_ģ������ ���忴demo
		B����ʵ��CPP�ļ���ENTITYDEF_CLASS_REGISTER��ʵ��ע�ᣬ���忴demo
*/
class Avatar : public GameObject, public Combat, public Motion, public State, public Flags, public Spell, public SkillBox, public Teleport, public AvatarLingGen
{
public:
	Avatar();
	virtual ~Avatar();

	virtual void __init__() override;

public:
	virtual void onDestroy() override;
	virtual void onEnterWorld() override;
	virtual void onLeaveWorld() override;
	virtual void onEnterSpace() override;
	virtual void onLeaveSpace() override;

	void reqRelive(uint8 reliveType);

public:
	// def�ж���Ŀͻ����漰����
	uint16 level;
	uint16 own_val;
};


/*
Declare all of the properties and methods of the KBE-Entity

Example:
	#define ENTITYDEF_DECLARE_[module name of Entity](PARENT_MODULE)	\
		ENTITYDEF_PROPERTY_*(PARENT_MODULE, xx_property)	\
		ENTITYDEF_METHOD_ARGS[0~20]_REGISTER(PARENT_MODULE, xx_method)
*/

#define ENTITYDEF_DECLARE_Avatar(PARENT_MODULE)	\
	ENTITYDEF_PROPERTY_REGISTER(PARENT_MODULE, level)	\
	ENTITYDEF_PROPERTY_REGISTER(PARENT_MODULE, own_val)
