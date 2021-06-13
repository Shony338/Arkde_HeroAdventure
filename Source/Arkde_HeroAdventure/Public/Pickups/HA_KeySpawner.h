// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_KeySpawner.generated.h"

class UBillboardComponent;
class AActor;
class AHA_Enemy;
class AHA_Key;
class AHA_PickUp;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_KeySpawner : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBillboardComponent* SpawnerBillboardComponent;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Spawner")
		TArray<AActor*> EnemyActors;

	UPROPERTY(BlueprintReadOnly, Category = "Spawner")
		TArray<AHA_Enemy*> EnemyCharacters;

	UPROPERTY(BlueprintReadOnly, Category = "Spawner")
		bool bHasSpawned;

	UPROPERTY(BlueprintReadOnly, Category = "Spawner")
		AHA_Key* KeySpawned;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawner")
		TSubclassOf<AHA_PickUp> KeyClass;
	
public:	
	// Sets default values for this actor's properties
	AHA_KeySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnKey();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BP_SpawnKey();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RemoveEnemy(AHA_Enemy* EnemyToRemove);
};
