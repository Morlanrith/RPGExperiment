// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include <RPGExperiment\AdditionalOperations.h>
#include "RoamingEnemy.generated.h"

USTRUCT(BlueprintType)
struct FEnemiesDataStructure : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FCombatantStruct Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ARoamingEnemy> EnemyType;
};

UCLASS()
class RPGEXPERIMENT_API ARoamingEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARoamingEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void CreateParty(TArray<FName> validEnemyTypes, FName thisEnemy);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsMoving = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UAdditionalOperations* Enemies;
};
