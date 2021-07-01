// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PartyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RPGEXPERIMENT_API APartyPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	APartyPlayerState();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UAdditionalOperations* PlayerParty;
};
