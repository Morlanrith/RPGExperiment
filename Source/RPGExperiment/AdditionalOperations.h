// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdditionalOperations.generated.h"

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
		int32 Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		int32 Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Struct")
		TArray<int32> AttackList;
	FCombatantStruct();
	FCombatantStruct(int HP, int atk, int def, int spd, TArray<int32> attacks);
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
	UFUNCTION(BlueprintCallable)
		void RemovePartyMember(int index);
	UFUNCTION(BlueprintCallable)
		int GetMemberMaxHP(int index);
	UFUNCTION(BlueprintCallable)
		int GetMemberCurrentHP(int index);
	UFUNCTION(BlueprintCallable)
		int GetMemberAttack(int index);
	UFUNCTION(BlueprintCallable)
		int GetMemberDefense(int index);
	UFUNCTION(BlueprintCallable)
		int GetMemberSpeed(int index);
	UFUNCTION(BlueprintCallable)
		TArray<int32> GetMemberAttackList(int index);
	UFUNCTION(BlueprintCallable)
		int GetPartySize();
	UFUNCTION(BlueprintCallable)
		int DamagePartyMember(int incomingAttack, int target, float attackMultiplier);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
		TArray<FCombatantStruct> GetParty();
	UFUNCTION(BlueprintCallable)
		void SetParty(TArray<FCombatantStruct> savedParty);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
		void AddPartyMember(int HP, int atk, int def, int spd, TArray<int32> attacks);
	void AddPartyMember(FCombatantStruct newMember);
		
};