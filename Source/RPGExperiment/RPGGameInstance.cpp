// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameInstance.h"
#include "MyPartySaveGame.h"

void URPGGameInstance::LoadSaveValues(USaveGame* savedGame) {
	UMyPartySaveGame* mySave = Cast<UMyPartySaveGame>(savedGame);
	CurrentParty = mySave->SavedParty;
	PlayerPosition = mySave->PlayerPos;
}

void URPGGameInstance::ResetValues() {
	EncounteredEnemy.Empty();
	RoamingEnemies.Empty();
	EnemyPositions.Empty();
	RoamingEnemyIDs.Empty();
	EnemyIndex = 0;
}