// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdditionalOperations.h"
#include "BossOperations.generated.h"

/**
 * 
 */
UCLASS()
class RPGEXPERIMENT_API UBossOperations : public UAdditionalOperations
{
	GENERATED_BODY()
public:
	int32 SelectAttack(UAdditionalOperations* playerParty);
};
