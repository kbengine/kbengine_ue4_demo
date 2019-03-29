// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/KBECommon.h"

#include "Engine/AccountBase.h"

namespace KBEngine
{

class Account : public AccountBase
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

	virtual void onCreateAvatarResult(uint8 retcode, const AVATAR_INFOS& info) override;
	virtual void onRemoveAvatar(uint64 dbid) override;
	virtual void onReqAvatarList(const AVATAR_INFOS_LIST& datas) override;

public:
	void onLastSelCharacterChanged(uint64 oldValue) override;

	AVATAR_INFOS_LIST characters;

};

}
