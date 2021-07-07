// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyParty.h"
#include "AdditionalOperations.h"

// Sets default values
AEnemyParty::AEnemyParty()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Enemies = CreateDefaultSubobject<UAdditionalOperations>(TEXT("An Enemy Party")); // Creates default additional operations component
	// Adds 1 to 3 basic enemies to party (should be changed later to use different types of enemy)
	for (int i = 0; i < rand() % 3 + 1; i++) {
		Enemies->AddPartyMember(40, 10, 3, 6, {0,3});
	}
}

// Called when the game starts or when spawned
void AEnemyParty::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyParty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

