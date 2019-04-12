// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Scripts/LogicEvents.h"
#include "GameFramework/GameMode.h"
#include "GameModeDemoBase.generated.h"

/**
 * 
 */
UCLASS()
class KBENGINE_UE4_DEMO_API AGameModeDemoBase : public AGameMode
{
	GENERATED_UCLASS_BODY()
	
public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called once this actor has been deleted */
	//virtual void Destroyed() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

	/**
	* Initialize the game.
	* The GameMode's InitGame() event is called before any other functions (including PreInitializeComponents() )
	* and is used by the GameMode to initialize parameters and spawn its helper classes.
	* @warning: this is called before actors' PreInitializeComponents.
	*/
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/** Called when a Controller with a PlayerState leaves the match. */
	virtual void Logout(AController* Exiting) override;

	/*
		安装登陆时需要监听的KBE事件
	*/
	virtual void installEvents();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	bool startRelogin;

	UFUNCTION(BlueprintCallable, Category = KBEngine)
	void fire(const FString& eventName, UKBEventData* pEventData);

	/* KBE事件
		玩家被踢出服务器
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onKicked(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onDisconnected(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onConnectionState(const UKBEventData* pEventData);
	
	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onReloginBaseappSuccessfully(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onReloginBaseappFailed(const UKBEventData* pEventData);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void startReloginBaseappTimer();

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void stopReloginBaseappTimer();

	//重登baseapp项目
	void onReloginBaseappTimer();

	FTimerHandle timerHandle;
};
