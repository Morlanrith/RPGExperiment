// Fill out your copyright notice in the Description page of Project Settings.


#include "ModelControl.h"

// Sets default values for this component's properties
UModelControl::UModelControl()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UModelControl::BeginPlay()
{
	DefaultCamera = Cast<ACameraActor>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget());
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UModelControl::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/*Creates the models for each combatant.*/
void UModelControl::CreateModels(TArray<FCombatantStruct> players, TArray<FCombatantStruct> enemies) 
{
	// Obtains a pointer to the data table for combatant models
	UDataTable* ModelDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/RPGContent/DataTables/ModelsDataTable.ModelsDataTable'"));
	for (int i = 0; i < players.Num(); i++) // Iterates for each player party member
		// Adds to the list of player party actors
		PlayerParty.Add(
			GetWorld()->SpawnActor<ACharacter>( // Spawns a character
				ModelDataTable->FindRow<FModelsDataStructure>(players[i].ModelID, FString())->Model, // Obtains the relevant model from the data table
				FTransform(FQuat(0.0f,0.0f,-180.0f,0.0f),FVector(DefaultLocation.X, DefaultLocation.Y - (300.0f * i), DefaultLocation.Z)) // Places each model at a determined offset from the default location
			)
		);
	for (int i = 0; i < enemies.Num(); i++) // Iterates for each enemy party member
		// Adds to the list of enemy party actors
		EnemyParty.Add(
			GetWorld()->SpawnActor<ACharacter>( // Spawns a character
				ModelDataTable->FindRow<FModelsDataStructure>(enemies[i].ModelID, FString())->Model, // Obtains the relevant model from the data table
				FTransform(FVector(DefaultLocation.X-600.0f, DefaultLocation.Y - (300.0f * i), DefaultLocation.Z)) // Places each model at a determined offset from the default location
				)
		);
}

/*Changes the camera to the relevant perspective.*/
void UModelControl::ChangeCamera(int32 playerToChangeTo) 
{
	AActor* viewTarget = DefaultCamera; // Sets the default viewing target to be the standard camera
	// If the player to change to is not less than 0, then sets that player as the default viewing target
	if (playerToChangeTo >= 0) viewTarget = PlayerParty[playerToChangeTo];
	GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(viewTarget); // Sets the player view to be the default viewing target
}

/*Hides the models of enemy party members at the given indexes.*/
void UModelControl::HideEnemyModels(TArray<int32> indexes)
{
	// Hides the Mesh of each model at the given indexes
	for (int i = 0; i < indexes.Num(); i++) EnemyParty[indexes[i]]->FindComponentByClass<UStaticMeshComponent>()->SetVisibility(false);
}

/*Destroys the models of enemy party members at the given indexes, and removes them from their model TArray.*/
void UModelControl::DestroyEnemyModels(TArray<int32> indexes)
{
	for (int i = 0; i < indexes.Num(); i++) {
		EnemyParty[indexes[i]]->Destroy(); // Destroys the model at the given index
		EnemyParty.RemoveAt(indexes[i]); // Removes the model at the given index from the enemy party TArray
	}
}