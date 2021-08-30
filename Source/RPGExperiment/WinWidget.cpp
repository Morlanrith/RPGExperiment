// Fill out your copyright notice in the Description page of Project Settings.


#include "WinWidget.h"

TArray<FCombatantStruct> UWinWidget::AddPartyExp(TArray<FCombatantStruct> party) {
	for (int i = 0; i < party.Num(); i++) {
		party[i].Exp += expEarned;
		while (party[i].Exp >= party[i].ExpNeeded && party[i].Level < 20) {
			party[i].Exp -= party[i].ExpNeeded;
			party[i].ExpNeeded *= 1.5f;
			party[i].Level++;
			party[i].MaxHP += party[i].Level % 2 == 0 ? party[i].HPGrowth : party[i].HPGrowth + 1;
			party[i].CurrentHP = party[i].MaxHP;
			party[i].Attack += party[i].Level % 2 == 0 ? party[i].AttackGrowth : party[i].AttackGrowth + 1;
			party[i].Defense += party[i].Level % 2 == 0 ? party[i].DefenseGrowth : party[i].DefenseGrowth + 1;
			party[i].Speed += party[i].Level % 2 == 0 ? party[i].SpeedGrowth : party[i].SpeedGrowth + 1;
		}
	}
	return party;
}