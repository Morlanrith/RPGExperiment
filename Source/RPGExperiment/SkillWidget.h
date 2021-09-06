// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleWidget.h"
#include "SkillWidget.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSkillInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info Struct")
		FName SkillName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info Struct")
		FText SkillInfo;

	FSkillInfoStruct();
	FSkillInfoStruct(FName name, FText info);
};

UCLASS()
class RPGEXPERIMENT_API USkillWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UFUNCTION(BlueprintCallable)
		TArray<FSkillInfoStruct> GetSkills();
};
