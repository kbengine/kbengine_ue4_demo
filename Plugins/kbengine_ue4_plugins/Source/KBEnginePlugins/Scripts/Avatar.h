// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/KBECommon.h"

#include "Engine/AvatarBase.h"

namespace KBEngine
{

class Avatar : public AvatarBase
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
	virtual void OnTeamData(uint8 arg1, const TArray<uint64>& arg2) {}
public:
	void onHPChanged(int32 oldValue) override;
	void onHP_MaxChanged(int32 oldValue) override;
	void onMPChanged(int32 oldValue) override;
	void onMP_MaxChanged(int32 oldValue) override;
	void onForbidsChanged(int32 oldValue) override;
	void onLevelChanged(uint16 oldValue) override;
	void onModelIDChanged(uint32 oldValue) override;
	void onModelScaleChanged(uint8 oldValue) override;
	void onMoveSpeedChanged(uint8 oldValue) override;
	void onNameChanged(const FString& oldValue) override;
	void onOwn_valChanged(uint16 oldValue) override;
	void onSpaceUTypeChanged(uint32 oldValue) override;
	void onStateChanged(int8 oldValue) override;
	void onSubStateChanged(uint8 oldValue) override;
	void onUidChanged(uint32 oldValue) override;
	void onUtypeChanged(uint32 oldValue) override;

public:
	void dialog_addOption(uint8 arg1, uint32 arg2, const FString& arg3, int32 arg4) override {}
	void dialog_close() override {}
	void dialog_setText(const FString& arg1, uint8 arg2, uint32 arg3, const FString& arg4) override {}

	void onAddSkill(int32 arg1) override;
	void onJump() override;
	void onRemoveSkill(int32 arg1) override;
	void recvDamage(int32 arg1, int32 arg2, int32 arg3, int32 arg4) override;
};

}
