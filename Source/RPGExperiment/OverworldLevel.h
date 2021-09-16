// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "RoamingEnemy.h"
#include "OverworldLevel.generated.h"

/**
 * 
 */
UCLASS()
class RPGEXPERIMENT_API AOverworldLevel : public ALevelScriptActor
{
	GENERATED_BODY()
private:
	ARoamingEnemy* CreateAnEnemy(TSubclassOf<class ARoamingEnemy> enemyType, FVector startLocation, FRotator startRotation);
	UFUNCTION(BlueprintCallable)
		void CreateEnemies(FVector startingLocation, TArray<FName> validEnemyTypes);
};
