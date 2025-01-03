// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSkill.h"
#include "../Controller/MainController.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

// Sets default values
UBaseSkill::UBaseSkill()
{
}

UBaseSkill::UBaseSkill(const TCHAR* Ref)
{
	ConstructorHelpers::FObjectFinder<UPaperSprite> SpriteRef(Ref);
	SkillSprite = SpriteRef.Object;
}

void UBaseSkill::BeginDestroy()
{
	Super::BeginDestroy();

	if (GetWorld()) {
		GetWorld()->GetTimerManager().ClearTimer(CountdownProgHandle);
	}
}


void UBaseSkill::PerformSkill()
{
	if (USkillComponent* SkillComponent = Cast<USkillComponent>(this->GetOuter())) {
		if (ABaseCharacter* OwningCharacter = SkillComponent->GetOwner<ABaseCharacter>()) {
			int OwnerMana = OwningCharacter->GetCurrentMana();
			if (OwnerMana > 0) {
				if (isAvailable && OwningCharacter->GetVelocity().Z == 0.0f) {
					OwningCharacter->SetCharacterState(CharacterState::USESKILL);
					if (AMainController* MainController = Cast<AMainController>(OwningCharacter->GetController())) {
						if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
							MainHUD->ShowSkillLoaderUI(this);
						}
					}
					isAvailable = false;
					GetWorld()->GetTimerManager().SetTimer(CountdownProgHandle, FTimerDelegate::CreateUObject(this, &UBaseSkill::CooldownSkill), 0.1f, true);
					OwningCharacter->GetAnimInstance()->JumpToNode(SKillName);
					OwningCharacter->SetManaAfterConsume(ManaConsumption);

				}
			}
		}
	}
}

void UBaseSkill::CooldownSkill()
{
	if (USkillComponent* SkillComponent = Cast<USkillComponent>(this->GetOuter())) {
		if (ABaseCharacter* OwningCharacter = SkillComponent->GetOwner<ABaseCharacter>()) {
			if (AMainController* MainController = Cast<AMainController>(OwningCharacter->GetController())) {
				if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
					CurrentCooldown += 0.1f;
					if (CurrentCooldown > CooldownTime) {
						this->isAvailable = true;
						CurrentCooldown = 0.0f;
						MainHUD->HideSkillLoaderUI(this);
						OwningCharacter->GetWorldTimerManager().ClearTimer(CountdownProgHandle);
						return;
					}
					MainHUD->UpdateSkillCountdownProgUI(this, CurrentCooldown / CooldownTime);
				}
			}
		}
	}
}


