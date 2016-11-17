// Fill out your copyright notice in the Description page of Project Settings.

#include "kbengine_ue4_demo.h"
#include "KBEMain.h"
#include "ClientApp.h"

// Sets default values
AClientApp::AClientApp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	pKBEMain = CreateDefaultSubobject<UKBEMain>(TEXT("KBEMain"));
}

// Called when the game starts or when spawned
void AClientApp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClientApp::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

