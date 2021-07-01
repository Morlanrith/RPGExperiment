// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGEXPERIMENT_API UBattleWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UFUNCTION(BlueprintCallable)
		void SetTarget(int speed, int attacker, int target, bool isPartyMember);
	UFUNCTION(BlueprintCallable)
		void ClearTargets();
	UFUNCTION(BlueprintCallable)
		void ClearPlayerTarget(int playerIndex);
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<int32> speedOrder;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<int32> indexSpeedOrder;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<int32> indexTargetOrder;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<bool> isPlayerSpeedOrder;
};

