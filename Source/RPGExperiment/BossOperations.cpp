// Fill out your copyright notice in the Description page of Project Settings.


#include "BossOperations.h"

int32 UBossOperations::SelectAttack(UAdditionalOperations* playerParty) {
	TArray<int32> attackIDs = GetMemberAttackList(0);
	if (GetMemberCurrentHP(0) > 650) return attackIDs[rand() % attackIDs.Num()];
	if (GetMemberBuff(0).BuffID == FName("-1")) return 15;
	return 0;
}