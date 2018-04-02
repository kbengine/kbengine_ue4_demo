// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameModeDemoBase.h"
#include "GameModeWorld.generated.h"

class AGameEntity;
class APlayerCharacter;

/**
 * 
 */
UCLASS()
class KBENGINE_UE4_DEMO_API AGameModeWorld : public AGameModeDemoBase
{
	GENERATED_UCLASS_BODY()

public:
	virtual void BeginPlay() override;

	/*
		安装登陆时需要监听的KBE事件
	*/
	virtual void installEvents() override;

	UFUNCTION(BlueprintCallable, Category = KBEngine)
	void reqRelive(int reliveType);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void addSpaceGeometryMapping(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onEnterWorld(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onEnterSpace(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onLeaveWorld(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onLeaveSpace(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_position(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_direction(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void updatePosition(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onControlled(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_HP(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_MP(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_HP_Max(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_MP_Max(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_level(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_name(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_moveSpeed(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_modelScale(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_modelID(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_entityNO(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_flags(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_state(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_subState(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void set_forbids(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void recvDamage(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void otherAvatarOnJump(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onAddSkill(const UKBEventData* pEventData);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	AGameEntity* findGameEntity(int entityID);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void addGameEntity(int entityID, AGameEntity* entity);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void removeGameEntity(int entityID);

	TMap<ENTITY_ID, AGameEntity*> gameEntities;

	// 在编辑器中配置相关类
	UPROPERTY(EditDefaultsOnly, Category = KBEngine)
	TArray<TSubclassOf<class AGameEntity>> GameEntityClassArray;

	// 在编辑器中配置相关类
	UPROPERTY(EditDefaultsOnly, Category = KBEngine)
	TArray<TSubclassOf<class APlayerCharacter>> PlayerCharacterClassArray;
	
};
