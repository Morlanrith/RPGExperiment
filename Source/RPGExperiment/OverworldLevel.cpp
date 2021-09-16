// Fill out your copyright notice in the Description page of Project Settings.


#include "OverworldLevel.h"
#include "RPGGameInstance.h"
#include "NavigationSystem.h"

/*Creates an enemy of the given subclass, in the given location.*/
ARoamingEnemy* AOverworldLevel::CreateAnEnemy(TSubclassOf<class ARoamingEnemy> enemyType, FVector startLocation, FRotator startRotation) {
	// Creates spawn parameters the ensure the enemy always spawns, but attempting to adjust if there are conflicts
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	// Spawns the enemy
	ARoamingEnemy* enemy = GetWorld()->SpawnActor<ARoamingEnemy>(enemyType, startLocation, startRotation, SpawnInfo);
	enemy->SpawnDefaultController(); // Makes sure the enemy's default controller is also created
	return enemy; // Returns the reference to the enemy
}

/*Creates enemies for the level space.*/
void AOverworldLevel::CreateEnemies(FVector startingLocation, TArray<FName> validEnemyTypes) {
	URPGGameInstance* myGame = Cast<URPGGameInstance>(GetGameInstance()); // Obtains the game instance
	// Loads the enemies data table
	UDataTable* enemiesDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/RPGContent/DataTables/EnemiesDataTable.EnemiesDataTable'"));
	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(GetWorld()); // Obtains the nav system for the level
	// Determines if enemies were already created or not
	if (myGame->RoamingEnemyIDs.Num() > 0) {
		// Recreates enemies in the positions they were in prior, with the exception of the enemy just encountered, replacing it instead
		for (int i = 0; i < myGame->RoamingEnemyIDs.Num(); i++) {
			// Attempts to use the recorded enemy's type ID and transformation
			FName index = myGame->RoamingEnemyIDs[i];
			FVector spawnLocation = myGame->EnemyPositions[i].GetLocation();
			FRotator spawnRotation = myGame->EnemyPositions[i].GetRotation().Rotator();
			// If the enemy was the one just fought, replaces it with a new random enemy
			if (myGame->EnemyIndex == i) {
				index = validEnemyTypes[rand() % validEnemyTypes.Num()];
				spawnLocation = navSystem->GetRandomReachablePointInRadius(GetWorld(), startingLocation, 5000.0f);
				spawnRotation = FRotator(0.0f, 0.0f, 0.0f);
			}
			// Spawns the enemy, storing a reference to it and its index
			myGame->RoamingEnemies[i] = CreateAnEnemy(enemiesDataTable->FindRow<FEnemiesDataStructure>(index, FString())->EnemyType,spawnLocation,spawnRotation);
			myGame->RoamingEnemyIDs[i] = index;
		}
		myGame->EnemyPositions.Empty(); // Empties the enemy positions array, as its values are no longer needed
	}
	else {
		// If no enemies have been made yet, populates the level with a random assortment of valid enemy types
		for (int i = 0; i < 3; i++) {
			FName randIndex = validEnemyTypes[rand() % validEnemyTypes.Num()]; // Gets a random valid index
			// Creates an enemy at a random location and adds it to the game instance enemies array
			myGame->RoamingEnemies.Add(
				CreateAnEnemy(
					enemiesDataTable->FindRow<FEnemiesDataStructure>(randIndex, FString())->EnemyType,
					navSystem->GetRandomReachablePointInRadius(GetWorld(), startingLocation, 5000.0f),
					FRotator(0.0f,0.0f,0.0f)
				)
			);
			myGame->RoamingEnemyIDs.Add(randIndex); // Adds the index too
		}
	}
}