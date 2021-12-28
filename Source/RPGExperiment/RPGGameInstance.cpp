// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameInstance.h"
#include "MyPartySaveGame.h"

void URPGGameInstance::LoadSaveValues(USaveGame* savedGame) {
	UMyPartySaveGame* mySave = Cast<UMyPartySaveGame>(savedGame);
	CurrentParty = mySave->SavedParty;
	PlayerPosition = mySave->PlayerPos;
	CurrentLevel = mySave->CurrentLevel;
}

void URPGGameInstance::ResetValues() {
	CurrentParty.Empty();
	PlayerPosition = FTransform(FQuat(0.0f, 0.0f, 179.999756f, 0.0f), FVector(8805.0f, -230.0f, 1874.008789f), FVector(1.0f, 1.0f, 1.0f));
	EncounteredEnemy.Empty();
	RoamingEnemies.Empty();
	EnemyPositions.Empty();
	RoamingEnemyIDs.Empty();
	EnemyIndex = 0;
	IsBossFight = false;
}

void URPGGameInstance::LevelTransition(FTransform newPos) {
	PlayerPosition = newPos;
	EncounteredEnemy.Empty();
	RoamingEnemies.Empty();
	EnemyPositions.Empty();
	RoamingEnemyIDs.Empty();
	EnemyIndex = 0;
}