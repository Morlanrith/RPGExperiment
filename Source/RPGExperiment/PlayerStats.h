// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RPGEXPERIMENT_API PlayerStats
{
private:
	int maxHP, currentHP, attack, defense, speed;
	TArray<int32> attackList;

public:
	PlayerStats(int HP, int atk, int def, int spd, TArray<int32> attacks);
	~PlayerStats();
	int MaxHP();
	int CurrentHP();
	int Attack();
	int Defense();
	int Speed();
	TArray<int32> AttackList();
	int Damage(int incomingAttack);
};
