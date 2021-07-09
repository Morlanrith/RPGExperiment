// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleWidget.h"

FTurnOrderStruct::FTurnOrderStruct()
{
	CombatantSpeed = 0;
	CombatantIndex = 0;
	CombatantTargetIndex = 0;
	CombatantAttackID = 0;
	CombatantIsPlayer = true;
}

FTurnOrderStruct::FTurnOrderStruct(int speed, int index, int target, int attackID, bool isPlayer)
{
	CombatantSpeed = speed;
	CombatantIndex = index;
	CombatantTargetIndex = target;
	CombatantAttackID = attackID;
	CombatantIsPlayer = isPlayer;
}

void UBattleWidget::SetTarget(int speed, int attacker, int target, int attackID, bool isPartyMember) {
	// Checks speed values of all set attacks for the turn, adding this combatant at their correct spot in the turn order
	FTurnOrderStruct newAction(speed, attacker, target, attackID, isPartyMember);
	for (int i = 0; i < turnOrder.Num(); i++) {
		if (speed > turnOrder[i].CombatantSpeed) {
			turnOrder.Insert(newAction, i);
			return;
		}
	}
	// Adds the combatant to the end of all lists as they are the slowest currently added
	turnOrder.Add(newAction);
}

void UBattleWidget::ClearTargets() {
	// Removes all turn selections for every combatant
	turnOrder.Empty();
}

void UBattleWidget::ClearPlayerTarget(int playerIndex) {
	// Searches for the player with the given index and removes them from the turn list
	for (int i = 0; i < turnOrder.Num(); i++) {
		if (playerIndex == turnOrder[i].CombatantIndex) {
			turnOrder.RemoveAt(i);
			return;
		}
	}
	return;
}