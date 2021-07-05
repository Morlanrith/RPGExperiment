// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyPlayerState.h"
#include "AdditionalOperations.h"

APartyPlayerState::APartyPlayerState() {
	PlayerParty = CreateDefaultSubobject<UAdditionalOperations>(TEXT("The Player Party")); // Creates default additional operations component
	// Adds 2 example party members (should be changed later to use save state)
	PlayerParty->AddPartyMember(999, 20, 3, 8, {1,2});
	PlayerParty->AddPartyMember(700, 8, 0, 10, {3});
}