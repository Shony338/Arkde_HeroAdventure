// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HA_HealthComponent.h"

UHA_HealthComponent::UHA_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHA_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UHA_HealthComponent::DamageTaken);
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateInitialHealth, this, &UHA_HealthComponent::UpdateInitialHealth, 0.2f, false);
}

void UHA_HealthComponent::UpdateInitialHealth()
{
	OnHealthUpdateDelegate.Broadcast(CurrentHealth, MaxHealth);
}

void UHA_HealthComponent::DamageTaken(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	// Damage applied if the healing bot is not healing
	if (bBotActive)
	{
		Damage /= DamageReduction;
	}
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);

	if (CurrentHealth == 0.0)
	{
		bIsDead = true;
	}

	OnHealthChangeDelegate.Broadcast(this, DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
	OnHealthUpdateDelegate.Broadcast(CurrentHealth, MaxHealth);

	if (bDebug)
	{
		UE_LOG(LogTemp, Log, TEXT("Damage applied: %s"), *FString::SanitizeFloat(Damage))
		UE_LOG(LogTemp, Log, TEXT("My health is: %s"), *FString::SanitizeFloat(CurrentHealth))
	}
}

void UHA_HealthComponent::SetBotAffected(bool bIsAffected, float BotDamageReduction)
{
	bBotActive = bIsAffected;
	DamageReduction = BotDamageReduction;
}
