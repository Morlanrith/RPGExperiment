// Fill out your copyright notice in the Description page of Project Settings.


#include "WinWidget.h"
#include "PartyPlayerState.h"
#include "BattleWidget.h"
#include "RPGGameInstance.h"
#include "Engine/DataTable.h"

/*Adds exp gained to the party and displays their current level information.*/
void UWinWidget::AddPartyExp(UVerticalBox* partyBox, UTextBlock* expText) {
	URPGGameInstance* myGame = Cast<URPGGameInstance>(GetGameInstance()); // Obtains the game instance
	// Loads the players data table
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/RPGContent/DataTables/PlayersDataTable.PlayersDataTable'"));
	UDataTable* aDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/RPGContent/DataTables/AttackTable.AttackTable'"));
	for (int i = 0; i < myGame->CurrentParty.Num(); i++) {
		// Obtains the row from the data table that is relevant to the current party member
		FPlayersDataStructure* pRow = pDataTable->FindRow<FPlayersDataStructure>(myGame->CurrentParty[i].ModelID, FString());
		UWrapBox* pBox = Cast<UWrapBox>(partyBox->GetChildAt(i)); // Obtains the next Wrap Box
		myGame->CurrentParty[i].Exp += expEarned; // Adds exp gained
		// Levels party member up if needed
		while (myGame->CurrentParty[i].Exp >= myGame->CurrentParty[i].ExpNeeded && myGame->CurrentParty[i].Level < 20) {
			myGame->CurrentParty[i].Exp -= myGame->CurrentParty[i].ExpNeeded;
			myGame->CurrentParty[i].ExpNeeded *= 1.5f;
			myGame->CurrentParty[i].Level++;
			myGame->CurrentParty[i].MaxHP += myGame->CurrentParty[i].Level % 2 == 0 ? myGame->CurrentParty[i].HPGrowth : myGame->CurrentParty[i].HPGrowth + 1;
			myGame->CurrentParty[i].CurrentHP = myGame->CurrentParty[i].MaxHP;
			myGame->CurrentParty[i].Attack += myGame->CurrentParty[i].Level % 2 == 0 ? myGame->CurrentParty[i].AttackGrowth : myGame->CurrentParty[i].AttackGrowth + 1;
			myGame->CurrentParty[i].Magic += myGame->CurrentParty[i].Level % 2 == 0 ? myGame->CurrentParty[i].MagicGrowth : myGame->CurrentParty[i].MagicGrowth + 1;
			myGame->CurrentParty[i].Defense += myGame->CurrentParty[i].Level % 2 == 0 ? myGame->CurrentParty[i].DefenseGrowth : myGame->CurrentParty[i].DefenseGrowth + 1;
			myGame->CurrentParty[i].Speed += myGame->CurrentParty[i].Level % 2 == 0 ? myGame->CurrentParty[i].SpeedGrowth : myGame->CurrentParty[i].SpeedGrowth + 1;
			// Checks if a new skill has been unlocked
			for (int j = 0; j < pRow->SkillLevels.Num(); j++) {
				if (myGame->CurrentParty[i].Level == pRow->SkillLevels[j]) {
					myGame->CurrentParty[i].AttackList.Add(pRow->Skills[j]); // Adds the skill to the party members available attacks
					// Shows which skill has been unlocked
					Cast<UTextBlock>(pBox->GetChildAt(4))->SetVisibility(ESlateVisibility::Visible);
					Cast<UTextBlock>(pBox->GetChildAt(4))->SetText(FText::FromString("Learned : " + aDataTable->FindRow<FAttackStruct>(FName(FString::FromInt(pRow->Skills[j])),FString())->AttackName.ToString()));
					break;
				}
			}
		}
		// Sets the portrait to the relevant image from the player row
		Cast<UImage>(pBox->GetChildAt(0))->SetBrushFromTexture(pRow->Portrait);
		Cast<UTextBlock>(pBox->GetChildAt(1))->SetText(FText::FromString(pRow->Name + " " + FString::FromInt(myGame->CurrentParty[i].CurrentHP) + "/" + FString::FromInt(myGame->CurrentParty[i].MaxHP)));
		Cast<UTextBlock>(pBox->GetChildAt(2))->SetText(FText::FromString("Level : " + FString::FromInt(myGame->CurrentParty[i].Level)));
		Cast<UTextBlock>(pBox->GetChildAt(3))->SetText(FText::FromString("To Next Level : " + FString::FromInt(myGame->CurrentParty[i].ExpNeeded - myGame->CurrentParty[i].Exp) + " EXP"));
		pBox->SetVisibility(ESlateVisibility::Visible); // Makes the current Wrap Box visible
	}
	expText->SetText(FText::FromString("Earned " + FString::FromInt(expEarned) + " EXP!"));
}