// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStats.h"

PlayerStats::PlayerStats(int HP, int atk, int def, int spd, TArray<int32> attacks)
{
	maxHP = HP;
	currentHP = HP;
	attack = atk;
	defense = def;
	speed = spd;
	attackList = attacks;
}

PlayerStats::~PlayerStats()
{
}

int PlayerStats::MaxHP() {
	return maxHP;
}

int PlayerStats::CurrentHP() {
	return currentHP;
}

int PlayerStats::Attack() {
	return attack;
}

int PlayerStats::Defense() {
	return defense;
}

int PlayerStats::Speed() {
	return speed;
}

TArray<int32> PlayerStats::AttackList() {
	return attackList;
}

int PlayerStats::Damage(int incomingAttack) {
	int damageDone = incomingAttack - defense; // Calculates damage amount
	if (damageDone < 0 || currentHP == 0) return currentHP; // Ignores attack if it has no effect/target has not health left
	int newHP = currentHP - damageDone; // Applies damage
	if (newHP < 0) newHP = 0;
	currentHP = newHP;
	return currentHP; // Returns new current health value
}

