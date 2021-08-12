// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Runtime\UMG\Public\UMG.h>
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGEXPERIMENT_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UFUNCTION(BlueprintCallable)
		void DisplayPauseMenu(UVerticalBox* partyBox);
};
