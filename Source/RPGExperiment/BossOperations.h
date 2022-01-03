// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdditionalOperations.h"
#include "BossOperations.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RPGEXPERIMENT_API UBossOperations : public UAdditionalOperations
{
	GENERATED_BODY()
public:
	int ultimateTick = 5;
	int absorbingHP = 400;
	int32 SelectAttack(UAdditionalOperations* playerParty);
};
