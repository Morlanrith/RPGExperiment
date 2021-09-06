// Fill out your copyright notice in the Description page of Project Settings.


#include "WinWidget.h"
#include "PartyPlayerState.h"
#include "BattleWidget.h"
#include "Engine/DataTable.h"

/*Adds exp gained to the party and displays their current level information.*/
TArray<FCombatantStruct> UWinWidget::AddPartyExp(TArray<FCombatantStruct> party, UVerticalBox* partyBox) {
	// Loads the players data table
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/RPGContent/DataTables/PlayersDataTable.PlayersDataTable'"));
	UDataTable* aDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/RPGContent/DataTables/AttackTable.AttackTable'"));
	for (int i = 0; i < party.Num(); i++) {
		// Obtains the row from the data table that is relevant to the current party member
		FPlayersDataStructure* pRow = pDataTable->FindRow<FPlayersDataStructure>(party[i].ModelID, FString());
		UWrapBox* pBox = Cast<UWrapBox>(partyBox->GetChildAt(i)); // Obtains the next Wrap Box
		party[i].Exp += expEarned; // Adds exp gained
		// Levels party member up if needed
		while (party[i].Exp >= party[i].ExpNeeded && party[i].Level < 20) {
			party[i].Exp -= party[i].ExpNeeded;
			party[i].ExpNeeded *= 1.5f;
			party[i].Level++;
			party[i].MaxHP += party[i].Level % 2 == 0 ? party[i].HPGrowth : party[i].HPGrowth + 1;
			party[i].CurrentHP = party[i].MaxHP;
			party[i].Attack += party[i].Level % 2 == 0 ? party[i].AttackGrowth : party[i].AttackGrowth + 1;
			party[i].Defense += party[i].Level % 2 == 0 ? party[i].DefenseGrowth : party[i].DefenseGrowth + 1;
			party[i].Speed += party[i].Level % 2 == 0 ? party[i].SpeedGrowth : party[i].SpeedGrowth + 1;
			// Checks if a new skill has been unlocked
			for (int j = 0; j < pRow->SkillLevels.Num(); j++) {
				if (party[i].Level == pRow->SkillLevels[j]) {
					party[i].AttackList.Add(pRow->Skills[j]); // Adds the skill to the party members available attacks
					// Shows which skill has been unlocked
					Cast<UTextBlock>(pBox->GetChildAt(4))->SetVisibility(ESlateVisibility::Visible);
					Cast<UTextBlock>(pBox->GetChildAt(4))->SetText(FText::FromString("Learned : " + aDataTable->FindRow<FAttackStruct>(FName(FString::FromInt(pRow->Skills[j])),FString())->AttackName.ToString()));
					break;
				}
			}
		}
		// Sets the portrait to the relevant image from the player row
		Cast<UImage>(pBox->GetChildAt(0))->SetBrushFromTexture(pRow->Portrait);
		Cast<UTextBlock>(pBox->GetChildAt(1))->SetText(FText::FromString(pRow->Name + " " + FString::FromInt(party[i].CurrentHP) + "/" + FString::FromInt(party[i].MaxHP)));
		Cast<UTextBlock>(pBox->GetChildAt(2))->SetText(FText::FromString("Level : " + FString::FromInt(party[i].Level)));
		Cast<UTextBlock>(pBox->GetChildAt(3))->SetText(FText::FromString("To Next Level : " + FString::FromInt(party[i].ExpNeeded - party[i].Exp) + " EXP"));
		pBox->SetVisibility(ESlateVisibility::Visible); // Makes the current Wrap Box visible
	}
	return party;
}