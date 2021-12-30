// Fill out your copyright notice in the Description page of Project Settings.


#include "BossOperations.h"

int32 UBossOperations::SelectAttack(UAdditionalOperations* playerParty) {
	if (GetMemberCurrentHP(0) > 900) return 0;
	ultimateTick--;
	if (!ultimateTick) {
		ultimateTick = 5;
		return 17;
	}
	if (ultimateTick == 1) return 16;
	if (GetMemberBuff(0).BuffID == FName("-1")) return 15;
	TArray<int32> _ = GetMemberAttackList(0);
	return _[rand() % _.Num()];
}

int UBossOperations::DamagePartyMember(int incomingAttack, int target, float attackMultiplier, bool absoluteDmg) {
	int damageDone = UAdditionalOperations::DamagePartyMember(incomingAttack, target, attackMultiplier, absoluteDmg);
	return damageDone;
}