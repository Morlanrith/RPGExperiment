// Fill out your copyright notice in the Description page of Project Settings.


#include "TPBar.h"

/*Updates the TP bar to show how much TP the party member has.*/
void UTPBar::UpdateTP(int newTP) {

	TArray<UWidget*> TP_Segments = TP_BarBox->GetAllChildren();
	for (int i = 0; i < TP_Segments.Num(); i++) // Iterates through each TP segment
		TP_Segments[i]->SetVisibility(i < newTP ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}