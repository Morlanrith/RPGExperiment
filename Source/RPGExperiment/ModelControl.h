// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <RPGExperiment\BattleWidget.h>
#include "ModelControl.generated.h"


USTRUCT(BlueprintType)
struct FModelsDataStructure : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ACharacter> Model;
};

UCLASS(Blueprintable)
class RPGEXPERIMENT_API UModelControl : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UModelControl();

private:
	UFUNCTION(BlueprintCallable)
		void CreateModels(TArray<FCombatantStruct> players, TArray<FCombatantStruct> enemies);
	UFUNCTION(BlueprintCallable)
		void ChangeCamera(int32 playerToChangeTo, bool isPartyMember = true);
	UFUNCTION(BlueprintCallable)
		void HideEnemyModels(TArray<int32> indexes);
	UFUNCTION(BlueprintCallable)
		void DestroyEnemyModels(TArray<int32> indexes);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector DefaultLocation = FVector(270.0f,-230.0f,118.0f);
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<ACharacter*> PlayerParty;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<ACharacter*> EnemyParty;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		ACameraActor* DefaultCamera;
		
};
