// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleWidget.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTurnOrderStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Order Struct")
		int32 CombatantSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Order Struct")
		int32 CombatantIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Order Struct")
		int32 CombatantTargetIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Order Struct")
		int32 CombatantAttackID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Order Struct")
		bool CombatantIsPlayer;

	FTurnOrderStruct();
	FTurnOrderStruct(int speed, int index, int target, int attackID, bool isPlayer);
};

UCLASS()
class RPGEXPERIMENT_API UBattleWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UFUNCTION(BlueprintCallable)
		void SetTarget(int speed, int attacker, int target, int attackID, bool isPartyMember);
	UFUNCTION(BlueprintCallable)
		void ClearTargets();
	UFUNCTION(BlueprintCallable)
		void ClearPlayerTarget(int playerIndex);
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<FTurnOrderStruct> turnOrder;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 turnAttackIndex = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool chooseTarget = true;
};

