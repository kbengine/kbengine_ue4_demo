// Fill out your copyright notice in the Description page of Project Settings.

#include "kbengine_ue4_demo.h"
#include "GameEntity.h"
#include "GameModeWorld.h"

// Sets default values
AGameEntity::AGameEntity(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	entityID = 0;
	moveSpeed = 0.f;
}

// Called when the game starts or when spawned
void AGameEntity::BeginPlay()
{
	Super::BeginPlay();
	
	auto XGameMode = Cast<AGameModeWorld>(UGameplayStatics::GetGameMode(this));
	
	if (XGameMode)
	{
		// 把自己注册到AGameModeWorld，方便后面查找
		XGameMode->addGameEntity(this->entityID, this);
	}
}

void AGameEntity::Destroyed()
{
	Super::Destroyed();

	auto XGameMode = Cast<AGameModeWorld>(UGameplayStatics::GetGameMode(this));

	if (XGameMode)
	{
		// 把自己注册到AGameModeWorld，方便后面查找
		XGameMode->removeGameEntity(this->entityID);
	}
}

// Called every frame
void AGameEntity::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AGameEntity::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

}

