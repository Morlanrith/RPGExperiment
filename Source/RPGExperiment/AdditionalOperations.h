// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <RPGExperiment\PlayerStats.h>
#include "AdditionalOperations.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGEXPERIMENT_API UAdditionalOperations : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAdditionalOperations();

private:
	TArray<PlayerStats> party;
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
		int GetPartySize();
	UFUNCTION(BlueprintCallable)
		int DamagePartyMember(int incomingAttack, int target);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
		void AddPartyMember(int HP, int atk, int def, int spd);
		
};
