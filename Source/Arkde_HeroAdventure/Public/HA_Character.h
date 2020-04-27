// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HA_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AHA_Weapon;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHA_Character();

	//Components

	//Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* TPSCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* SpringArmComponent;

	//Variables
protected:

	//Player Basic Movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
		bool bIsLookInverted;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		float walkSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FVector MovementDirection;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FVector ForwardMovementVector;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FVector RightMovementVector;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FRotator PlayerRotation;

	//Abilities
	//Evade
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Evade")
		float ImpulseStrenght;

	UPROPERTY(BlueprintReadOnly, Category = "Physics|Evade")
		float defaultGroundFriction;

	UPROPERTY(BlueprintReadOnly, Category = "Timers|Evade")
		FTimerHandle EvadeFrictionTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timers|Evade")
		FTimerHandle EvadeCooldown;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Evade")
		FVector LaunchStrenght;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Evade")
		bool bIsEvadeAvailable;

	//Pickups
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key")
		TArray<FName> KeyTags;

	//Weapons
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		TSubclassOf<AHA_Weapon> InitialWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		AHA_Weapon* CurrentWeapon;

public:

	//Player Basic Movement
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FRotator tempRotation;

	//Player Basic Gameplay
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
		bool bIsDoingAction;
	
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
		bool bIsAiming;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Jump
	virtual void Jump() override;
	virtual void StopJumping() override;

	//Movement
	void MoveForward(float value);
	void MoveRight(float value);

	void CalculateMovementDirection();
	void SetPlayerRotation();

	//Evade
	void Evade();
	void CooldownFinishedEvade();
	void RestoreFriction();
	
	//Action
	void ExecutingAction();
	void StopAction();
	
	//Aiming
	void Aiming();
	void StopAiming();

	//Attack
	void StartAttack();
	void StopAttack();

	void SetInitialWeapon();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement
	virtual void AddControllerPitchInput(float value) override;

	//Pickups
	void AddKey(FName NewKey);
	bool HasKey(FName Keytag);

	//Gameplay
	virtual FVector GetPawnViewLocation() const override;
};
