// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <RPGExperiment\PlayerStats.h>

/**
 * 
 */
class RPGEXPERIMENT_API PartyMemberStats : public PlayerStats
{
public:
	PartyMemberStats(int HP, int atk, int def, int spd, TArray<int32> attacks) :PlayerStats(HP, atk, def, spd, attacks) {}
	~PartyMemberStats();
};
