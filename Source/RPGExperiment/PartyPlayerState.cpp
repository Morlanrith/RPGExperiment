// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyPlayerState.h"
#include "AdditionalOperations.h"

APartyPlayerState::APartyPlayerState() {
	PlayerParty = CreateDefaultSubobject<UAdditionalOperations>(TEXT("The Player Party")); // Creates default additional operations component
	// Adds 2 example party members (should be changed later to use save state)
	PlayerParty->AddPartyMember(550, 20, 1, 10, {1,2}, FName(TEXT("0")));
	PlayerParty->AddPartyMember(800, 18, 5, 4, {3}, FName(TEXT("1")));
}