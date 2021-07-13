// Fill out your copyright notice in the Description page of Project Settings.


#include "RoamingEnemy.h"
#include "AdditionalOperations.h"

// Sets default values
ARoamingEnemy::ARoamingEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoamingEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARoamingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARoamingEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

