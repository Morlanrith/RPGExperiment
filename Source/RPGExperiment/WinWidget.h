// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AdditionalOperations.h"
#include <Runtime\UMG\Public\UMG.h>
#include "WinWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGEXPERIMENT_API UWinWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void AddPartyExp(UVerticalBox* partyBox, UTextBlock* expText);
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 expEarned = 0;
};
