// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RPGEXPERIMENT_API Attack
{
private:
	int attackID;
	float damageMultiplier;
	std::string attackName;

public:
	Attack(int ID, float mult, std::string name);
	~Attack();
	int AttackID();
	float DamageMultiplier();
	std::string AttackName();
};
