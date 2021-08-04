// Fill out your copyright notice in the Description page of Project Settings.


#include "RoamingEnemy.h"
#include "AdditionalOperations.h"

// Sets default values
ARoamingEnemy::ARoamingEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Enemies = CreateDefaultSubobject<UAdditionalOperations>(TEXT("An Enemy Party"));
}

// Called when the game starts or when spawned
void ARoamingEnemy::BeginPlay()
{
	UDataTable* EnemiesDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/RPGContent/DataTables/EnemiesDataTable.EnemiesDataTable'"));
	if (AvailableEnemies.Num() == 0) return;
	Enemies->AddPartyMemberStruct(EnemiesDataTable->FindRow<FEnemiesDataStructure>(AvailableEnemies[0], FString())->Stats);
	for (int i = 0; i < rand() % 3; i++) {
		Enemies->AddPartyMemberStruct(EnemiesDataTable->FindRow<FEnemiesDataStructure>(AvailableEnemies[rand() % AvailableEnemies.Num()], FString())->Stats);
	}
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

