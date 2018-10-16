// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GameEntity.generated.h"

const int ModelID_NPC = 1002;
const int ModelID_Monster1 = 1003;
const int ModelID_Monster2 = 1004;
const int ModelID_Gate = 40001001;
const int ModelID_Avatar = 90000001;

UCLASS()
class KBENGINE_UE4_DEMO_API AGameEntity : public ACharacter
{
	GENERATED_UCLASS_BODY()

public:
	// Sets default values for this character's properties
	AGameEntity();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/** Called once this actor has been deleted */
	virtual void Destroyed() override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	virtual bool isPlayer() {
		return false;
	}

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f) override;

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void updateLocation(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void setTargetLocation(const FVector& loc) 
	{
		targetLocation = loc;
	}

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void setTargetRotator(const FRotator& rot) 
	{
		targetRotator = rot;
	}

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void setIsOnGround(bool onGround)
	{
		isOnGround = onGround;
	}

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	virtual void setModelID(int modelID);

private:
	void createAvatar();
	void createMonster();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	float modelScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int modelID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	float moveSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;

	// 实体将要移动到的目的地位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FVector targetLocation;

	// 实体将要移动到的目的朝向
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FRotator targetRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	bool isOnGround;
};
