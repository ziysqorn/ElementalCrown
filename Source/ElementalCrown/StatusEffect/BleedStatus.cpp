#include "BleedStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

BleedStatus::BleedStatus() : BaseStatusEffect(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Impact/AttackHit/Blood/1_007_Sprite.1_007_Sprite'"), TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Impact/AttackHit/Blood/Effect_Impact_AttackHit_Blood.Effect_Impact_AttackHit_Blood'"))
{
	StatusName = "Bleed";
	AffectingTime = 8.0f;
}

BleedStatus::~BleedStatus()
{
	if (AffectedCharacter) {
		if (AffectedCharacter->GetWorldTimerManager().IsTimerActive(EffectHandle)) AffectedCharacter->GetWorldTimerManager().ClearTimer(EffectHandle);
		if (AffectedCharacter->GetWorldTimerManager().IsTimerActive(EffectEndHandle)) AffectedCharacter->GetWorldTimerManager().ClearTimer(EffectEndHandle);
	}
}

void BleedStatus::ExecuteStatus()
{
	if (OwningCharacter && AffectedCharacter) {
		StatusFlipbookComp = NewObject<UPaperFlipbookComponent>(AffectedCharacter, UPaperFlipbookComponent::StaticClass());
		StatusFlipbookComp->RegisterComponent();
		StatusFlipbookComp->AttachToComponent(AffectedCharacter->GetSprite(), FAttachmentTransformRules::KeepRelativeTransform);
		StatusFlipbookComp->SetRelativeLocation(FVector(0.0f, 5.0f, -5.0f));
		StatusFlipbookComp->SetRelativeScale3D(FVector(1.0f, 0.0f, 1.0f));
		StatusFlipbookComp->SetFlipbook(StatusFlipbook);
		StatusFlipbookComp->PlayFromStart();
		AffectedCharacter->GetWorldTimerManager().SetTimer(EffectEndHandle, FTimerDelegate::CreateLambda([this]() {
			if (OwningCharacter && AffectedCharacter) {
				StatusFlipbookComp->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
				AffectedCharacter->GetStatusList()->RemoveNodeByValue(this);
			}
			}), AffectingTime, false);
		AffectedCharacter->GetWorldTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda([this]() {
			if (OwningCharacter && AffectedCharacter) {
				TSubclassOf<UDamageType> DamageType;
				UGameplayStatics::ApplyDamage(AffectedCharacter, BleedDamage, OwningCharacter->GetController(), OwningCharacter, DamageType);
			}
			}), TimeBetweenEachHit, true);
	}
}
