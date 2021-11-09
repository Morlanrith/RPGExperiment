// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdditionalOperations.h"
#include "Engine/DataTable.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
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

USTRUCT(BlueprintType)
struct FAttackNumberStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Number Struct")
		int32 DamageValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Number Struct")
		int32 Target;

	FAttackNumberStruct();
	FAttackNumberStruct(int damage, int target);
};

USTRUCT(BlueprintType)
struct FAttackStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Struct")
		FName AttackName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Struct")
		int32 TPCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Struct")
		float DamageMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Struct")
		int32 TargetNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Struct")
		int32 AttackType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Struct")
		bool SelectTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Struct")
		bool AttackAll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Struct")
		FName AppliedBuff = FName("-1");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Struct")
		int32 AnimationEnumID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Struct")
		UParticleSystem* ParticleFX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Struct")
		FText AttackInfo;
};

UCLASS()
class RPGEXPERIMENT_API UBattleWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	int RandomTarget(UAdditionalOperations* dParty);
	UFUNCTION(BlueprintCallable)
		void ChooseEnemyAttacks(UAdditionalOperations* enemyParty, UAdditionalOperations* playerParty);
	UFUNCTION(BlueprintCallable)
		void SetTarget(int speed, int attacker, int target, int attackID, bool isPartyMember);
	UFUNCTION(BlueprintCallable)
		void SelectAlly(UAdditionalOperations* playerParty, UCanvasPanel* allyCanvas);
	TArray<FAttackNumberStruct> FireHeal(FAttackStruct tableRow, int aIndex, int dIndex, UAdditionalOperations* aParty);
	UFUNCTION(BlueprintCallable)
		TArray<FAttackNumberStruct> FireAttack(FAttackStruct tableRow, int aIndex, int dIndex, UAdditionalOperations* aParty, UAdditionalOperations* dParty);
	UFUNCTION(BlueprintCallable)
		TArray<int32> UpdatePlayerHP(UAdditionalOperations* playerParty, UVerticalBox* HPContainer, UVerticalBox* BuffContainer);
	UFUNCTION(BlueprintCallable)
		TArray<int32> UpdateEnemyHP(UAdditionalOperations* enemyParty, UVerticalBox* HPContainer, UVerticalBox* BuffContainer);
	UFUNCTION(BlueprintCallable)
		TArray<int32> EndingTurn(UAdditionalOperations* enemyParty, UVerticalBox* HPContainer, UVerticalBox* BuffContainer);
	UFUNCTION(BlueprintCallable)
		bool EndBattleCleanup(UAdditionalOperations* playerParty);
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
		int32 expEarned = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool chooseTarget = true;
};

