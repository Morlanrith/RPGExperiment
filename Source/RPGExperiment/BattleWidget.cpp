// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleWidget.h"
#include "PartyPlayerState.h"
#include "TPBar.h"

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
	UDataTable* attackTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/RPGContent/DataTables/AttackTable.AttackTable'"));
	for (int i = 0; i < enemyParty->GetPartySize(); i++) { // Iterates through each enemy
		TArray<int32> attackIDs = enemyParty->GetMemberAttackList(i); // Obtains the list of the enemy's attack indexes
		int32 randAttack = attackIDs[rand() % attackIDs.Num()];
		if (attackTable->FindRow<FAttackStruct>(FName(FString::FromInt(randAttack)), FString())->TPCost > enemyParty->GetMemberCurrentTP(i)) randAttack = 0;
		// Sets the enemies target to be a valid random party member, using a random attack from their list
		SetTarget(enemyParty->GetMemberSpeed(i),i,RandomTarget(playerParty), randAttack,false);
	}
}

/*Present allies you can choose to use the chosen skill on.*/
void UBattleWidget::SelectAlly(UAdditionalOperations* playerParty, UCanvasPanel* allyCanvas) {
	UDataTable* playerTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/RPGContent/DataTables/PlayersDataTable.PlayersDataTable'"));
	allyCanvas->SetVisibility(ESlateVisibility::Visible);
	for (int i = 0; i < playerParty->GetPartySize(); i++) {
		UButton* playerButton = Cast<UButton>(allyCanvas->GetChildAt(i+2));
		playerButton->SetVisibility(ESlateVisibility::Visible);
		playerButton->SetIsEnabled(playerParty->GetMemberCurrentHP(i)>0);
		Cast<UTextBlock>(playerButton->GetChildAt(0))->SetText(FText::FromString(playerTable->FindRow<FPlayersDataStructure>(playerParty->GetMemberModelID(i), FString())->Name));
	}
}

/*Fires the curent combatants heal.*/
TArray<FAttackNumberStruct> UBattleWidget::FireHeal(FAttackStruct tableRow, int aIndex, int dIndex, UAdditionalOperations* aParty) {
	if (tableRow.AttackAll) { // Checks to see if the chosen heal is supposed to affect all ally combatants, or just one
		TArray<FAttackNumberStruct> attackValues; // Creates an empty TArray of attack values to return
		// Loops over each member of the party
		for (int i = 0; i < aParty->GetPartySize(); i++) {
			if (aParty->GetMemberCurrentHP(i) == 0) continue; // Moves to the next combatant if this target has no HP remaining
			// Adds a value to the TArray, containing the heal value fired at the ally combatant, using HealPartyMember()
			attackValues.Add(FAttackNumberStruct(aParty->HealPartyMember(aParty->GetMemberMagic(aIndex), i, tableRow.DamageMultiplier), i));
			if(tableRow.AppliedBuff != FName("-1")) aParty->ApplyBuff(i, tableRow.AppliedBuff);
		}
		return attackValues; // Returns the array of attack values
	}
	// If the attack is individual, then checks to see if the combatant has no HP remaining, or if the combatants attack doesn't let them pick a target
	if (aParty->GetMemberCurrentHP(dIndex) == 0 || !tableRow.SelectTarget) {
		// If this is the case, then a target must be chosen randomly from the remaining combatants
		dIndex = RandomTarget(aParty);
	}
	if (tableRow.AppliedBuff != FName("-1")) aParty->ApplyBuff(dIndex, tableRow.AppliedBuff);
	// Returns a TArray containing the single heal value fired at the ally combatant, using HealPartyMember()
	return TArray<FAttackNumberStruct>({ FAttackNumberStruct(aParty->HealPartyMember(aParty->GetMemberMagic(aIndex), dIndex, tableRow.DamageMultiplier),dIndex) });
}

/*Attempts to fire the curent combatants attack.*/
TArray<FAttackNumberStruct> UBattleWidget::FireAttack(FAttackStruct tableRow, int aIndex, int dIndex, UAdditionalOperations* aParty, UAdditionalOperations* dParty, float QTEBoost) {
	if(aParty->GetMemberCurrentHP(aIndex) == 0) return TArray<FAttackNumberStruct>(); // Returns nothing if the attacker has no HP remaining
	int32 damageStat = 0;
	if (tableRow.AttackType == 3)
		return FireHeal(tableRow, aIndex, dIndex, aParty);
	else if (tableRow.AttackType == 1) damageStat = aParty->GetMemberAttack(aIndex);
	else if (tableRow.AttackType == 2) damageStat = aParty->GetMemberMagic(aIndex);
	else if (tableRow.AttackType == 4) {
		aParty->ApplyBuff(aIndex,tableRow.AppliedBuff);
		return TArray<FAttackNumberStruct>();
	}
	if (tableRow.AttackAll) { // Checks to see if the chosen attack is supposed to hit all enemy combatants, or just one
		TArray<FAttackNumberStruct> attackValues; // Creates an empty TArray of attack values to return
		// Loops over each member of the opposing party
		for (int i = 0; i < dParty->GetPartySize(); i++) {
			if (dParty->GetMemberCurrentHP(i) == 0) continue; // Moves to the next combatant if this target has no HP remaining
			// Adds a value to the TArray, containing the damage value fired at the enemy combatant, using DamagePartyMember()
			attackValues.Add(FAttackNumberStruct(dParty->DamagePartyMember(damageStat, i, tableRow.DamageMultiplier*QTEBoost),i));
			if (tableRow.AppliedBuff != FName("-1")) dParty->ApplyBuff(i, tableRow.AppliedBuff);
		}
		return attackValues; // Returns the array of attack values
	}
	// If the attack is individual, then checks to see if the defending combatant has no HP remaining, or if the combatants attack doesn't let them pick a target
	if (dParty->GetMemberCurrentHP(dIndex) == 0 || !tableRow.SelectTarget) {
		// If this is the case, then a target must be chosen randomly from the remaining defending combatants
		dIndex = RandomTarget(dParty);
		if (dIndex == -1) return TArray<FAttackNumberStruct>(); // Returns nothing if there are no enemy combatants remaining
	}
	if (tableRow.AppliedBuff != FName("-1")) dParty->ApplyBuff(dIndex, tableRow.AppliedBuff);
	// Returns a TArray containing the single damage value fired at the enemy combatant, using DamagePartyMember()
	return TArray<FAttackNumberStruct>({ FAttackNumberStruct(dParty->DamagePartyMember(damageStat, dIndex, tableRow.DamageMultiplier*QTEBoost),dIndex) });
}

/*Updates the UI display for the player party's HP values.*/
TArray<int32> UBattleWidget::UpdatePlayerHP(UAdditionalOperations* playerParty, UVerticalBox* HPContainer, UVerticalBox* BuffContainer, UVerticalBox* TPContainer) {
	UDataTable* buffTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/RPGContent/DataTables/BuffsDataTable.BuffsDataTable'"));
	TArray<int32> defeatIndexes; // Empty array for players that need to play their defeat animation
	for (int i = 0; i < playerParty->GetPartySize(); i++) { // Iterates through each party member
		UTextBlock* HPText = Cast<UTextBlock>(HPContainer->GetChildAt(i)); // Casts child i of the passed in container to a Text Block object
		UImage* BuffImage = Cast<UImage>(BuffContainer->GetChildAt(i));
		Cast<UTPBar>(TPContainer->GetChildAt(i))->UpdateTP(playerParty->GetMemberCurrentTP(i)); // Updates the TP bar for this party member
		// Sets the text to show the party members current HP information
		HPText->SetText(FText::FromString(FString::FromInt(playerParty->GetMemberCurrentHP(i)) + "/" + FString::FromInt(playerParty->GetMemberMaxHP(i))));
		HPText->SetVisibility(ESlateVisibility::Visible); // Makes sure the HP label is visible
		if (playerParty->GetMemberCurrentHP(i) == 0) defeatIndexes.Add(i); // If the party member has no HP remaining, list them in the defeat array
		if (playerParty->GetMemberBuff(i).BuffID != FName("-1")) {
			BuffImage->SetVisibility(ESlateVisibility::Visible);
			BuffImage->SetBrushFromTexture(buffTable->FindRow<FBuffRowStruct>(playerParty->GetMemberBuff(i).BuffID, FString())->Icon);
		}
		else BuffImage->SetVisibility(ESlateVisibility::Hidden);
	}
	return defeatIndexes; // Returns a list of indexes for players that are defeated
}

/*Updates the UI display for the enemy party's HP values.*/
TArray<int32> UBattleWidget::UpdateEnemyHP(UAdditionalOperations* enemyParty, UVerticalBox* HPContainer, UVerticalBox* BuffContainer) {
	UDataTable* buffTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/RPGContent/DataTables/BuffsDataTable.BuffsDataTable'"));
	TArray<int32> hideIndexes; // Empty array for enemies that need to have their models hidden
	for (int i = 0; i < enemyParty->GetPartySize(); i++) { // Iterates through each party member
		UBorder* HPBorder = Cast<UBorder>(HPContainer->GetChildAt(i)); // Casts child i of the passed in container to a Border object
		UImage* BuffImage = Cast<UImage>(BuffContainer->GetChildAt(i));
		if (enemyParty->GetMemberCurrentHP(i) == 0) {
			hideIndexes.Add(i); // If the party member has no HP remaining, adds them to the hide array
			HPBorder->SetVisibility(ESlateVisibility::Collapsed); // Also collapses the border containing their HP information
			BuffImage->SetVisibility(ESlateVisibility::Collapsed);
			continue;
		}
		HPBorder->SetVisibility(ESlateVisibility::Visible); // If the party member is still alive, makes sure their label is visible
		// Then, obtains the child of the current border, and sets its text label to reflect the current value of their HP
		Cast<UTextBlock>(HPBorder->GetChildAt(0))->SetText(FText::FromString(FString::FromInt(enemyParty->GetMemberCurrentHP(i)) + "/" + FString::FromInt(enemyParty->GetMemberMaxHP(i))));
		if (enemyParty->GetMemberBuff(i).BuffID != FName("-1")) {
			BuffImage->SetVisibility(ESlateVisibility::Visible);
			BuffImage->SetBrushFromTexture(buffTable->FindRow<FBuffRowStruct>(enemyParty->GetMemberBuff(i).BuffID, FString())->Icon);
		}
		else BuffImage->SetVisibility(ESlateVisibility::Hidden);
	}
	return hideIndexes; // Returns a list of indexes for enemies that are defeated
}

/*Cleans up hidden enemy party members that were defeated in the now finished turn.*/
TArray<int32> UBattleWidget::EndingTurn(UAdditionalOperations* enemyParty, UVerticalBox* HPContainer, UVerticalBox* BuffContainer) {
	ClearTargets(); // Clears out the set list of targets (in preparation for a new turn)
	TArray<int32> destroyIndexes; // Empty array for enemies that need to have their models destroyed
	for (int i = enemyParty->GetPartySize()-1; i >= 0; i--) { // Iterates backwards through each party member
		if (enemyParty->GetMemberCurrentHP(i) == 0) { // If the enemy has been defeated
			expEarned += enemyParty->GetMemberExp(i); // Adds enemy EXP to the earned EXP pool for the battle
			enemyParty->RemovePartyMember(i); // Removes them from their associated AdditionalOperations component
			HPContainer->RemoveChildAt(enemyParty->GetPartySize()); // Removes the last border from the HP container
			BuffContainer->RemoveChildAt(enemyParty->GetPartySize()); // Removes the last border from the HP container
			destroyIndexes.Add(i); // Adds the index to the list of indexes for models to be destroyed
		}
	}
	enemyParty->TickBuffsAndTP();
	return destroyIndexes; // Returns a list of indexes for enemies that are defeated
}

/*Cleans up health and buffs for the player party when the battle has ended.*/
bool UBattleWidget::EndBattleCleanup(UAdditionalOperations* playerParty) {
	bool defeated = true;
	for (int i = 0; i < playerParty->GetPartySize(); i++) {
		if (playerParty->GetMemberBuff(i).BuffID != FName("-1"))
			playerParty->RemoveBuff(i);
		if (playerParty->GetMemberCurrentHP(i) == 0)
			playerParty->HealPartyMember(1,i,1.0f);
		else defeated = false;
		playerParty->AddTP(i, playerParty->GetMemberMaxTP(i));
	}
	return defeated;
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