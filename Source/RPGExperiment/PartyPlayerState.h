// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include <Runtime\UMG\Public\UMG.h>
#include "AdditionalOperations.h"
#include "PartyPlayerState.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayersDataStructure : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FCombatantStruct Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Portrait;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int> Skills;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int> SkillLevels;
};

UCLASS()
class RPGEXPERIMENT_API APartyPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	APartyPlayerState();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UAdditionalOperations* PlayerParty;
};
