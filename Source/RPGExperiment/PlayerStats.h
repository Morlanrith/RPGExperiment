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

public:
	PlayerStats(int HP, int atk, int def, int spd);
	~PlayerStats();
	int MaxHP();
	int CurrentHP();
	int Attack();
	int Defense();
	int Speed();
	int Damage(int incomingAttack);
};
