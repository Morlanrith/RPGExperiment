// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyPlayerState.h"

APartyPlayerState::APartyPlayerState() {
	PlayerParty = CreateDefaultSubobject<UAdditionalOperations>(TEXT("The Player Party")); // Creates default additional operations component
}