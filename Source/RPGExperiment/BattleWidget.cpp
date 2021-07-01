// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleWidget.h"

void UBattleWidget::SetTarget(int speed, int attacker, int target, bool isPartyMember) {
	// Checks speed values of all set attacks for the turn, adding this combatant at their correct spot in the turn order
	for (int i = 0; i < speedOrder.Num(); i++) {
		if (speed > speedOrder[i]) {
			speedOrder.Insert(speed, i);
			indexSpeedOrder.Insert(attacker, i);
			indexTargetOrder.Insert(target, i);
			isPlayerSpeedOrder.Insert(isPartyMember, i);
			return;
		}
	}
	// Adds the combatant to the end of all lists as they are the slowest currently added
	speedOrder.Add(speed);
	indexSpeedOrder.Add(attacker);
	indexTargetOrder.Add(target);
	isPlayerSpeedOrder.Add(isPartyMember);
}

void UBattleWidget::ClearTargets() {
	// Removes all turn selections for every combatant (should be changed later to use less TArrays, i.e. when stats are separated into player/enemy classes)
	speedOrder.Empty();
	indexSpeedOrder.Empty();
	indexTargetOrder.Empty();
	isPlayerSpeedOrder.Empty();
}

void UBattleWidget::ClearPlayerTarget(int playerIndex) {
	// Searches for the player with the given index and removes them from all lists (should be changed later)
	for (int i = 0; i < indexSpeedOrder.Num(); i++) {
		if (playerIndex == indexSpeedOrder[i]) {
			speedOrder.RemoveAt(i);
			indexSpeedOrder.RemoveAt(i);
			indexTargetOrder.RemoveAt(i);
			isPlayerSpeedOrder.RemoveAt(i);
			return;
		}
	}
	return;
}