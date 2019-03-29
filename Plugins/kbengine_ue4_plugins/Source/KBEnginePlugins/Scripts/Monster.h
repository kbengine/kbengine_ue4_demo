// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/KBECommon.h"

#include "Engine/MonsterBase.h"

namespace KBEngine
{

class Monster : public MonsterBase
{
public:
	Monster();
	virtual ~Monster();

public:
	void recvDamage(int32 arg1, int32 arg2, int32 arg3, int32 arg4) override;

public:
	virtual void onHPChanged(int32 oldValue) override;
	virtual void onHP_MaxChanged(int32 oldValue) override;
	virtual void onMPChanged(int32 oldValue) override;
	virtual void onMP_MaxChanged(int32 oldValue) override;
	virtual void onEntityNOChanged(uint32 oldValue) override;
	virtual void onForbidsChanged(int32 oldValue) override;
	virtual void onModelIDChanged(uint32 oldValue) override;
	virtual void onModelScaleChanged(uint8 oldValue) override;
	virtual void onMoveSpeedChanged(uint8 oldValue) override;
	virtual void onNameChanged(const FString& oldValue) override;
	virtual void onStateChanged(int8 oldValue) override;
	virtual void onSubStateChanged(uint8 oldValue) override;
	virtual void onUidChanged(uint32 oldValue) override;
	virtual void onUtypeChanged(uint32 oldValue) override;

};

}


