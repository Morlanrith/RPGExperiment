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

void UAdditionalOperations::AddPartyMember(int HP, int atk, int def, int spd) {
	PlayerStats newMember(HP, atk, def, spd);
	party.Add(newMember);
}

void UAdditionalOperations::RemovePartyMember(int index) {
	party.RemoveAt(index);
}

int UAdditionalOperations::GetPartySize() {
	return party.Num();
}

int UAdditionalOperations::GetMemberMaxHP(int index) {
	return party[index].MaxHP();
}

int UAdditionalOperations::GetMemberCurrentHP(int index) {
	return party[index].CurrentHP();
}

int UAdditionalOperations::GetMemberAttack(int index) {
	return party[index].Attack();
}

int UAdditionalOperations::GetMemberDefense(int index) {
	return party[index].Defense();
}

int UAdditionalOperations::GetMemberSpeed(int index) {
	return party[index].Speed();
}

int UAdditionalOperations::DamagePartyMember(int incomingAttack, int target) {
	return party[target].Damage(incomingAttack);
}

