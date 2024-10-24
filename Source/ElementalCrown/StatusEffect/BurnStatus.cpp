// Fill out your copyright notice in the Description page of Project Settings.


#include "BurnStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

BurnStatus::BurnStatus() : BaseStatusEffect(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/StatusEffect/Burn/Sprite/burning_loop_1_Sprite_6.burning_loop_1_Sprite_6'"))
{
	StatusName = "Burn";
	AffectingTime = 4.0f;
}

void BurnStatus::ExecuteStatus()
{
	if (OwningCharacter && AffectedCharacter) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwningCharacter;
		if (ABurn* BurnEffect = AffectedCharacter->GetWorld()->SpawnActor<ABurn>(ABurn::StaticClass(), AffectedCharacter->GetActorLocation(), AffectedCharacter->GetActorRotation(), SpawnParams)) {
			BurnEffect->AttachToActor(AffectedCharacter, FAttachmentTransformRules::KeepRelativeTransform);
			BurnEffect->SetActorRelativeLocation(FVector(0.0f, 3.0f, 0.0f));
			BurnEffect->SetActorRelativeScale3D(FVector(2.0f, 0.0f, 3.0f));
			AffectedCharacter->GetWorldTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda([this, BurnEffect]() {
				if (OwningCharacter && AffectedCharacter) {
					TSubclassOf<UDamageType> DamageType;
					UGameplayStatics::ApplyDamage(AffectedCharacter, BurnDamage, OwningCharacter->GetController(), OwningCharacter, DamageType);
					TimeElapsed += TimeBetweenEachBurn;
					if (TimeElapsed >= AffectingTime) {
						AffectedCharacter->GetWorldTimerManager().ClearTimer(EffectHandle);
						BurnEffect->Destroy();
						auto CurStatusList = AffectedCharacter->GetStatusList();
						for (int i = 0; i < CurStatusList->Num(); ++i) {
							TSharedPtr<BaseStatusEffect> cur = (*CurStatusList)[i];
							if (cur->GetStatusName() == "Burn") CurStatusList->RemoveAt(i);
						}
					}
				}
				}), TimeBetweenEachBurn, true);
		}
	}
}


