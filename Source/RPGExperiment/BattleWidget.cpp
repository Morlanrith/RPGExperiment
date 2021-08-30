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

FAttackNumberStruct::FAttackNumberStruct() {
	DamageValue = 0;
	Target = 0;
}

FAttackNumberStruct::FAttackNumberStruct(int damage, int target) {
	DamageValue = damage;
	Target = target;
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

/*Selects a random target from the defending party that has not already been defeated.*/
int UBattleWidget::RandomTarget(UAdditionalOperations* dParty) {
	TArray<int> validTargets; // Array of potentially valid party indexes
	for (int i = 0; i < dParty->GetPartySize(); i++) // Iterates through each member of the defending party
		if (dParty->GetMemberCurrentHP(i) > 0) validTargets.Add(i); // If the current party member has any HP remaining, it is considered a valid target
	if (validTargets.Num() == 0) return -1; // If there are no valid targets, -1 is returned to signal this to FireAttack()
	return validTargets[rand() % validTargets.Num()]; // Otherwise, returns a random party member index from the valid options
}

/*Randomly sets each of the enemy party members attacks.*/
void UBattleWidget::ChooseEnemyAttacks(UAdditionalOperations* enemyParty, UAdditionalOperations* playerParty) {
	for (int i = 0; i < enemyParty->GetPartySize(); i++) { // Iterates through each enemy
		TArray<int32> attackIDs = enemyParty->GetMemberAttackList(i); // Obtains the list of the enemy's attack indexes
		// Sets the enemies target to be a valid random party member, using a random attack from their list
		SetTarget(enemyParty->GetMemberSpeed(i),i,RandomTarget(playerParty), attackIDs[rand() % attackIDs.Num()],false);
	}
}

/*Attempts to fire the curent combatants attack.*/
TArray<FAttackNumberStruct> UBattleWidget::FireAttack(FAttackStruct tableRow, int aIndex, int dIndex, UAdditionalOperations* aParty, UAdditionalOperations* dParty) {
	if(aParty->GetMemberCurrentHP(aIndex) == 0) return TArray<FAttackNumberStruct>(); // Returns nothing if the attacker has no HP remaining
	if (tableRow.AttackAll) { // Checks to see if the chosen attack is supposed to hit all enemy combatants, or just one
		TArray<FAttackNumberStruct> attackValues; // Creates an empty TArray of attack values to return
		// Loops over each member of the opposing party
		for (int i = 0; i < dParty->GetPartySize(); i++) {
			if (dParty->GetMemberCurrentHP(i) == 0) continue; // Moves to the next combatant if this target has no HP remaining
			// Adds a value to the TArray, containing the damage value fired at the enemy combatant, using DamagePartyMember()
			attackValues.Add(FAttackNumberStruct(dParty->DamagePartyMember(aParty->GetMemberAttack(aIndex), i, tableRow.DamageMultiplier),i));
		}
		return attackValues; // Returns the array of attack values
	}
	// If the attack is individual, then checks to see if the defending combatant has no HP remaining, or if the combatants attack doesn't let them pick a target
	if (dParty->GetMemberCurrentHP(dIndex) == 0 || !tableRow.SelectTarget) {
		// If this is the case, then a target must be chosen randomly from the remaining defending combatants
		dIndex = RandomTarget(dParty);
		if (dIndex == -1) return TArray<FAttackNumberStruct>(); // Returns nothing if there are no enemy combatants remaining
	}
	// Returns a TArray containing the single damage value fired at the enemy combatant, using DamagePartyMember()
	return TArray<FAttackNumberStruct>({ FAttackNumberStruct(dParty->DamagePartyMember(aParty->GetMemberAttack(aIndex), dIndex, tableRow.DamageMultiplier),dIndex) });
}

/*Updates the UI display for the player party's HP values.*/
TArray<int32> UBattleWidget::UpdatePlayerHP(UAdditionalOperations* playerParty, UVerticalBox* HPContainer) {
	TArray<int32> defeatIndexes; // Empty array for players that need to play their defeat animation
	for (int i = 0; i < playerParty->GetPartySize(); i++) { // Iterates through each party member
		UTextBlock* HPText = Cast<UTextBlock>(HPContainer->GetChildAt(i)); // Casts child i of the passed in container to a Text Block object
		// Sets the text to show the party members current HP information
		HPText->SetText(FText::FromString(FString::FromInt(playerParty->GetMemberCurrentHP(i)) + "/" + FString::FromInt(playerParty->GetMemberMaxHP(i))));
		HPText->SetVisibility(ESlateVisibility::Visible); // Makes sure the HP label is visible
		if (playerParty->GetMemberCurrentHP(i) == 0) defeatIndexes.Add(i); // If the party member has no HP remaining, list them in the defeat array
	}
	return defeatIndexes; // Returns a list of indexes for players that are defeated
}

/*Updates the UI display for the enemy party's HP values.*/
TArray<int32> UBattleWidget::UpdateEnemyHP(UAdditionalOperations* enemyParty, UVerticalBox* HPContainer) {
	TArray<int32> hideIndexes; // Empty array for enemies that need to have their models hidden
	for (int i = 0; i < enemyParty->GetPartySize(); i++) { // Iterates through each party member
		UBorder* HPBorder = Cast<UBorder>(HPContainer->GetChildAt(i)); // Casts child i of the passed in container to a Border object
		if (enemyParty->GetMemberCurrentHP(i) == 0) {
			hideIndexes.Add(i); // If the party member has no HP remaining, adds them to the hide array
			HPBorder->SetVisibility(ESlateVisibility::Collapsed); // Also collapses the border containing their HP information
			continue;
		}
		HPBorder->SetVisibility(ESlateVisibility::Visible); // If the party member is still alive, makes sure their label is visible
		// Then, obtains the child of the current border, and sets its text label to reflect the current value of their HP
		Cast<UTextBlock>(HPBorder->GetChildAt(0))->SetText(FText::FromString(FString::FromInt(enemyParty->GetMemberCurrentHP(i)) + "/" + FString::FromInt(enemyParty->GetMemberMaxHP(i))));
	}
	return hideIndexes; // Returns a list of indexes for enemies that are defeated
}

/*Cleans up hidden enemy party members that were defeated in the now finished turn.*/
TArray<int32> UBattleWidget::EndingTurn(UAdditionalOperations* enemyParty, UVerticalBox* HPContainer) {
	ClearTargets(); // Clears out the set list of targets (in preparation for a new turn)
	TArray<int32> destroyIndexes; // Empty array for enemies that need to have their models destroyed
	for (int i = enemyParty->GetPartySize()-1; i >= 0; i--) { // Iterates backwards through each party member
		if (enemyParty->GetMemberCurrentHP(i) == 0) { // If the enemy has been defeated
			expEarned += enemyParty->GetMemberExp(i); // Adds enemy EXP to the earned EXP pool for the battle
			enemyParty->RemovePartyMember(i); // Removes them from their associated AdditionalOperations component
			HPContainer->RemoveChildAt(enemyParty->GetPartySize()); // Removes the last border from the HP container
			destroyIndexes.Add(i); // Adds the index to the list of indexes for models to be destroyed
		}
	}
	return destroyIndexes; // Returns a list of indexes for enemies that are defeated
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