// Fill out your copyright notice in the Description page of Project Settings.


#include "AdditionalOperations.h"

// Sets default values for this component's properties
UAdditionalOperations::UAdditionalOperations()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

FCombatantStruct::FCombatantStruct()
{
	MaxHP = 1;
	CurrentHP = 1;
	Attack = 1;
	Defense = 0;
	Speed = 1;
	AttackList = {};
	ModelID = FName(TEXT("0"));
}

FCombatantStruct::FCombatantStruct(int HP, int atk, int def, int spd, TArray<int32> attacks, FName modelID)
{
	MaxHP = HP;
	CurrentHP = HP;
	Attack = atk;
	Defense = def;
	Speed = spd;
	AttackList = attacks;
	ModelID = modelID;
}


// Called when the game starts
void UAdditionalOperations::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAdditionalOperations::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAdditionalOperations::AddPartyMember(int HP, int atk, int def, int spd, TArray<int32> attacks, FName modelID) {
	FCombatantStruct newMember(HP, atk, def, spd, attacks, modelID);
	party.Add(newMember);
}

void UAdditionalOperations::AddPartyMemberStruct(FCombatantStruct newMember) {
	party.Add(newMember);
}

void UAdditionalOperations::RemovePartyMember(int index) {
	party.RemoveAt(index);
}

int UAdditionalOperations::GetPartySize() {
	return party.Num();
}

int UAdditionalOperations::GetMemberMaxHP(int index) {
	return party[index].MaxHP;
}

int UAdditionalOperations::GetMemberCurrentHP(int index) {
	return party[index].CurrentHP;
}

int UAdditionalOperations::GetMemberAttack(int index) {
	return party[index].Attack;
}

int UAdditionalOperations::GetMemberDefense(int index) {
	return party[index].Defense;
}

int UAdditionalOperations::GetMemberSpeed(int index) {
	return party[index].Speed;
}

TArray<int32> UAdditionalOperations::GetMemberAttackList(int index) {
	return party[index].AttackList;
}

int UAdditionalOperations::DamagePartyMember(int incomingAttack, int target, float attackMultiplier) {
	int damageValue = incomingAttack * attackMultiplier;
	int damageDone = damageValue - party[target].Defense; // Calculates damage amount
	if (damageDone < 0 || party[target].CurrentHP == 0) return party[target].CurrentHP; // Ignores attack if it has no effect/target has not health left
	int newHP = party[target].CurrentHP - damageDone; // Applies damage
	if (newHP < 0) newHP = 0;
	party[target].CurrentHP = newHP;
	return newHP;
}

TArray<FCombatantStruct> UAdditionalOperations::GetParty()
{
	return party;
}

void UAdditionalOperations::SetParty(TArray<FCombatantStruct> savedParty)
{
	party = savedParty;
}

