#include "BleedStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

BleedStatus::BleedStatus() : BaseStatusEffect(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Impact/AttackHit/Blood/1_007_Sprite.1_007_Sprite'"))
{
	StatusName = "Bleed";
	AffectingTime = 8.0f;
}

BleedStatus::~BleedStatus()
{
}

void BleedStatus::ExecuteStatus()
{
	if (OwningCharacter && AffectedCharacter) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwningCharacter;
		if (ABleed* BleedEffect = AffectedCharacter->GetWorld()->SpawnActor<ABleed>(ABleed::StaticClass(), AffectedCharacter->GetActorLocation(), AffectedCharacter->GetActorRotation(), SpawnParams)) {
			BleedEffect->AttachToActor(AffectedCharacter, FAttachmentTransformRules::KeepRelativeTransform);
			BleedEffect->SetActorRelativeLocation(FVector(0.0f, 3.0f, 2.0f));
			BleedEffect->SetActorRelativeScale3D(FVector(2.0f, 0.0f, 3.0f));
			AffectedCharacter->GetWorldTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda([this, BleedEffect]() {
				if (OwningCharacter && AffectedCharacter) {
					TSubclassOf<UDamageType> DamageType;
					UGameplayStatics::ApplyDamage(AffectedCharacter, BleedDamage, OwningCharacter->GetController(), OwningCharacter, DamageType);
					if(AffectedCharacter->GetCharacterState() != CharacterState::DEATH) BleedEffect->BloodSpray();
					TimeElapsed += TimeBetweenEachHit;
					if (TimeElapsed >= AffectingTime) {
						AffectedCharacter->GetWorldTimerManager().ClearTimer(EffectHandle);
						BleedEffect->Destroy();
						auto CurStatusList = AffectedCharacter->GetStatusList();
						for (int i = 0; i < CurStatusList->Num(); ++i) {
							TSharedPtr<BaseStatusEffect> cur = (*CurStatusList)[i];
							if (cur->GetStatusName() == "Bleed") CurStatusList->RemoveAt(i);
						}
					}
				}
				}), TimeBetweenEachHit, true);
		}
	}
}
