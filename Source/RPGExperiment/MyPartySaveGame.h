// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AdditionalOperations.h"
#include "MyPartySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class RPGEXPERIMENT_API UMyPartySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        TArray<FCombatantStruct> SavedParty;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        FTransform PlayerPos;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        int32 UserIndex;

    UMyPartySaveGame();
};
