// Fill out your copyright notice in the Description page of Project Settings.


#include "BossOperations.h"

int32 UBossOperations::SelectAttack(UAdditionalOperations* playerParty) {
	if (GetMemberCurrentHP(0) >= 600) return 0; // If the fight has just started, use a basic attack
	TArray<FCombatantStruct> bossParty = GetParty();
	ultimateTick--; // Begin ticking for ultimate attack
	switch (ultimateTick) {
		case 2: // Begin charging ultimate attack
			bossParty[0].Speed = 0;
			SetParty(bossParty);
			return 16;
		case 1: // Continue charging, start tracking damage taken
			absorbingHP = GetMemberCurrentHP(0);
			return 16;
		case 0: // Fire ultimate attack
			bossParty[0].Magic += (absorbingHP - GetMemberCurrentHP(0));
			bossParty[0].Speed = 999;
			SetParty(bossParty);
			return 17;
		case -1: // Repair stats after firing ultimate attack
			ultimateTick = 4;
			bossParty[0].Magic = 25; // Set to default magic value
			bossParty[0].Speed = 12; // Set to default speed value
			SetParty(bossParty);
	}
	if (GetMemberBuff(0).BuffID == FName("-1")) return 15; // If the intangible buff is not active, apply it
	// Select and return a random attack from the boss' standard list of skills
	TArray<int32> _ = GetMemberAttackList(0);
	return _[rand() % _.Num()];
}