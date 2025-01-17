// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HA_GameMode.generated.h"

class AHA_Character;
class AHA_SpectatingCamera;
class AHA_Enemy;
class AHA_MazeZone;
class USoundCue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyKilledSignature, float, EnemiesKilledAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStateChangeSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMapZoneChangeSignature, bool, bIsAlertMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerOverlapSignature);

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Level")
		bool bIsInMaze;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
		FName MapName;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
		AHA_SpectatingCamera* VictoryCamera;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
		AHA_SpectatingCamera* GameOverCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spectating Camera")
		float CameraBlendTime;

	UPROPERTY(BlueprintReadOnly, Category = "Death counter")
		float EnemiesKilled;

	FTimerHandle TimerHandle_BackToMainMenu;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music")
		USoundCue* VictoryMusic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music")
		USoundCue* GameOverMusic;

	UPROPERTY(BlueprintReadOnly, Category = "Music")
		AHA_MazeZone* MazeLevel;

public:
	UPROPERTY(BlueprintAssignable)
	FOnGameStateChangeSignature OnVictoryDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnGameStateChangeSignature OnGameOverDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnMapZoneChangeSignature OnMapZoneChangeDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnEnemyKilledSignature OnEnemyKilledDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerOverlapSignature OnPlayerOverlapDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerOverlapSignature OnPlayerExitOverlapDelegate;

protected:
	virtual void BeginPlay() override;

	//Camera control
	void SetUpSpectatingCameras();

	void ChangeToSpectatorCamera(AHA_Character* Character, AHA_SpectatingCamera* SpectatorCamera);

	//Gamecore control
	void BackToMainMenu();

	void PlayMusic(USoundCue* GameMusic);
			
public:
	AHA_GameMode();

	//Gamecore contorl
	void CheckAlerts();

	UFUNCTION()
	void Victory(AHA_Character* Character);

	UFUNCTION()
	void GameOver(AHA_Character* Character); 
	
	UFUNCTION(BlueprintImplementableEvent)
		void BP_Victory(AHA_Character* Character);

	UFUNCTION(BlueprintImplementableEvent)
		void BP_GameOver(AHA_Character* Character);

	UFUNCTION()
		void DestroySceneObject(AActor* ThisActor, float TimeToDestroy);

	UFUNCTION(BlueprintImplementableEvent)
		void BP_DestroySceneObject(AActor* ThisActor, float TimeToDestroy);

	//Player information control
	UFUNCTION()
	void AddKeyToCharacter(AHA_Character* KeyOwner, FName KeyTag);

	void AddEnemyKilled();

	void PickUpOverlap(bool bIsOverlapping);
};
