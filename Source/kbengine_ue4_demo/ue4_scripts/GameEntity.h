// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GameEntity.generated.h"

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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	float moveSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;
};
