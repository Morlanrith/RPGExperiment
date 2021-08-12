// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "AdditionalOperations.h"
#include "PartyPlayerState.h"
#include "Engine/DataTable.h"

/*Displays the information for each party member.*/
void UPauseWidget::DisplayPauseMenu(UVerticalBox* partyBox) {
	// Loads the players data table
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/RPGContent/DataTables/PlayersDataTable.PlayersDataTable'"));
	// Obtains the player party from the player state
	UAdditionalOperations* pParty = Cast<APartyPlayerState>(GetWorld()->GetGameState()->PlayerArray[0])->PlayerParty;
	for (int i = 0; i < pParty->GetPartySize(); i++) { // Iterates through each party member
		UWrapBox* pBox = Cast<UWrapBox>(partyBox->GetChildAt(i)); // Obtains the next Wrap Box
		// Obtains the row from the data table that is relevant to the current party member
		FPlayersDataStructure* pRow = pDataTable->FindRow<FPlayersDataStructure>(pParty->GetMemberModelID(i), FString());
		// Sets the portrait to the relevant image from the player row
		Cast<UImage>(pBox->GetChildAt(0))->SetBrushFromTexture(pRow->Portrait);
		// Sets the text to display the party members name and current health information
		Cast<UTextBlock>(pBox->GetChildAt(1))->SetText(FText::FromString(pRow->Name + " " + FString::FromInt(pParty->GetMemberCurrentHP(i)) + "/" + FString::FromInt(pParty->GetMemberMaxHP(i))));
		pBox->SetVisibility(ESlateVisibility::Visible); // Makes the current Wrap Box visible
	}
}