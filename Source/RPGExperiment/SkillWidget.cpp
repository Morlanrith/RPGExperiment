// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillWidget.h"
#include "PartyPlayerState.h"

FSkillInfoStruct::FSkillInfoStruct() {
	SkillName = FName("");
	SkillInfo = FText::FromString("");
	SkillCost = 0;
}

FSkillInfoStruct::FSkillInfoStruct(FName name, FText info, int32 cost) {
	SkillName = name;
	SkillInfo = info;
	SkillCost = cost;
}

TArray<FSkillInfoStruct> USkillWidget::GetSkills() {
	TArray<FSkillInfoStruct> skillList;
	UDataTable* aDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/RPGContent/DataTables/AttackTable.AttackTable'"));
	// Obtains the player party from the player state
	UAdditionalOperations* pParty = Cast<APartyPlayerState>(GetWorld()->GetGameState()->PlayerArray[0])->PlayerParty;
	for (int i = 0; i < pParty->GetPartySize(); i++) { // Iterates through each party member
		TArray<int32> skills = pParty->GetMemberAttackList(i);
		for (int j = 0; j < skills.Num(); j++) {
			FAttackStruct* skill = aDataTable->FindRow<FAttackStruct>(FName(FString::FromInt(skills[j])), FString());
			bool addSkill = true;
			for (int k = 0; k < skillList.Num(); k++)
				if (skillList[k].SkillName == skill->AttackName) addSkill = false;
			if(addSkill) 
				skillList.Add(FSkillInfoStruct(skill->AttackName, skill->AttackInfo, skill->TPCost));
		}
	}
	return skillList;
}