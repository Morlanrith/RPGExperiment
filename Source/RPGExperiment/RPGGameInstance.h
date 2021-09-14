// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AdditionalOperations.h"
#include "RoamingEnemy.h"
#include "RPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPGEXPERIMENT_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	UFUNCTION(BlueprintCallable)
		void LoadSaveValues(USaveGame* savedGame);
	UFUNCTION(BlueprintCallable)
		void ResetValues();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FCombatantStruct> CurrentParty;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FCombatantStruct> EncounteredEnemy;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<ARoamingEnemy*> RoamingEnemies;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FName> RoamingEnemyIDs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FTransform PlayerPosition = FTransform(FQuat(0.0f,0.0f,179.999756f,0.0f),FVector(8805.0f, -230.0f, 1874.008789f),FVector(1.0f,1.0f,1.0f));
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FTransform> EnemyPositions;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 EnemyIndex = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 CurrentSaveSlot = -1;
};
