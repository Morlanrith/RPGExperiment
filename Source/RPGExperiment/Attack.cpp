// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack.h"

Attack::Attack(int ID, float mult, std::string name)
{
	attackID = ID;
	damageMultiplier = mult;
	attackName = name;
}

Attack::~Attack()
{
}

int Attack::AttackID() {
	return attackID;
}

float Attack::DamageMultiplier() {
	return damageMultiplier;
}

std::string Attack::AttackName()
{
	return attackName;
}