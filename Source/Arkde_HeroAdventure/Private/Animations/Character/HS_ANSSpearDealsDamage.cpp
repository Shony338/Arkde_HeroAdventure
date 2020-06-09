// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Character/HS_ANSSpearDealsDamage.h"
#include "HA_Character.h"
#include "Components/CapsuleComponent.h"
#include "Weapons/HA_Spear.h"

void UHS_ANSSpearDealsDamage::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	AActor* ThisActor = MeshComp->GetOwner();
	if (IsValid(ThisActor))
	{
		AHA_Character* PlayerCharacter = Cast<AHA_Character>(ThisActor);
		if (IsValid(PlayerCharacter))
		{
			switch (PlayerCharacter->GetAttackSelected())
			{
			case 0:
				UE_LOG(LogTemp, Warning, TEXT("Right hand enabled"));
				PlayerCharacter->RightHandSpearComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				break;
			case 1:
				UE_LOG(LogTemp, Warning, TEXT("Left hand enabled"));
				PlayerCharacter->LeftHandSpearComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				break;
			default:
				break;
			}

		}
	}
}

void UHS_ANSSpearDealsDamage::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	AActor* ThisActor = MeshComp->GetOwner();
	if (IsValid(ThisActor))
	{
		AHA_Character* PlayerCharacter = Cast<AHA_Character>(ThisActor);
		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->RightHandSpearComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			PlayerCharacter->LeftHandSpearComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}