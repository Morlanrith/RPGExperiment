// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "TPBar.generated.h"

/**
 * 
 */
UCLASS()
class RPGEXPERIMENT_API UTPBar : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateTP(int newTP);
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UHorizontalBox* TP_BarBox;
};
