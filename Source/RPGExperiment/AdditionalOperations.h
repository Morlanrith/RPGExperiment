// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdditionalOperations.generated.h"

USTRUCT(BlueprintType)
struct FAttackDelay
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		int32 AttackTypeID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		float AnimationDelay;

	FAttackDelay();
	FAttackDelay(int typeID, float delay);
};

USTRUCT(BlueprintType)
struct FBuffStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff Struct")
		float Augmentation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff Struct")
		int32 ValueToChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff Struct")
		int32 RemainingTurns;

	FBuffStruct();
	FBuffStruct(float aug, int valType, int turns);
};

USTRUCT(BlueprintType)
struct FCombatantStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		int32 MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		int32 CurrentHP;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		int32 Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		int32 Magic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		int32 Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		int32 Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		FName ModelID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		TArray<int32> AttackList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		TArray<FBuffStruct> Buffs = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		int32 Exp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		int32 ExpNeeded;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		float HPGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		float AttackGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		float MagicGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		float DefenseGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		float SpeedGrowth;

	FCombatantStruct();
	FCombatantStruct(int HP, int atk, int mag, int def, int spd, TArray<int32> attacks, FName modelID, int lvl, int expNeeded, float HPG, float atkG, float magG, float defG, float spdG);
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGEXPERIMENT_API UAdditionalOperations : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAdditionalOperations();

private:

	TArray<FCombatantStruct> party;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
		void RemovePartyMember(int index);
	UFUNCTION(BlueprintCallable)
		int GetMemberMaxHP(int index);
	UFUNCTION(BlueprintCallable)
		int GetMemberCurrentHP(int index);
	UFUNCTION(BlueprintCallable)
		int GetMemberAttack(int index);
	UFUNCTION(BlueprintCallable)
		int GetMemberMagic(int index);
	UFUNCTION(BlueprintCallable)
		int GetMemberDefense(int index);
	UFUNCTION(BlueprintCallable)
		int GetMemberSpeed(int index);
	UFUNCTION(BlueprintCallable)
		TArray<int32> GetMemberAttackList(int index);
	UFUNCTION(BlueprintCallable)
		FName GetMemberModelID(int index);
	UFUNCTION(BlueprintCallable)
		int GetMemberExp(int index);
	UFUNCTION(BlueprintCallable)
		int GetMemberExpNeeded(int index);
	UFUNCTION(BlueprintCallable)
		int GetMemberLevel(int index);
	UFUNCTION(BlueprintCallable)
		int GetPartySize();
	UFUNCTION(BlueprintCallable)
		int DamagePartyMember(int incomingAttack, int target, float attackMultiplier);
	UFUNCTION(BlueprintCallable)
		int HealPartyMember(int healAmount, int target, float healMultiplier);
	UFUNCTION(BlueprintCallable)
		void ApplyBuff(int target, FBuffStruct buff);
	UFUNCTION(BlueprintCallable)
		void RemoveBuff(int target, int buffIndex);
	UFUNCTION(BlueprintCallable)
		void TickBuffs();
	UFUNCTION(BlueprintCallable)
		void RemoveAllBuffs();
	UFUNCTION(BlueprintCallable)
		TArray<FCombatantStruct> GetParty();
	UFUNCTION(BlueprintCallable)
		void SetParty(TArray<FCombatantStruct> savedParty);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
		void AddPartyMember(int HP, int atk, int mag, int def, int spd, TArray<int32> attacks, FName modelID, int lvl, int expNeeded, float HPG, float atkG, float magG, float defG, float spdG);
	UFUNCTION(BlueprintCallable)
		void AddPartyMemberStruct(FCombatantStruct newMember);
		
};