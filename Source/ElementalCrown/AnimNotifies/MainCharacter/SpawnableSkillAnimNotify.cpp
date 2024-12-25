// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableSkillAnimNotify.h"

void USpawnableSkillAnimNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (OwningInstance->GetOwningActor()) {
		if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OwningInstance->GetOwningActor())) {
			float CurrentPlaybackTime = OwningInstance->GetPlayer()->GetCurrentPlaybackTime();
			float CurrentAnimSequenceDuration = OwningInstance->GetPlayer()->GetCurrentAnimSequence()->GetTotalDuration();
			BaseCharacter->GetWorldTimerManager().SetTimer(FinishSkill, FTimerDelegate::CreateLambda([BaseCharacter]() {
				if (BaseCharacter) {
					BaseCharacter->SetCharacterState(CharacterState::NONE);
					BaseCharacter->GetCharacterMovement()->GravityScale = 1.0f;
				}
				}), CurrentAnimSequenceDuration - CurrentPlaybackTime, false);
			if (BaseCharacter->GetCharacterState() != CharacterState::SHOOT && BaseCharacter->GetCharacterMovement()->JumpZVelocity != 0.0f) {
				BaseCharacter->GetCharacterMovement()->GravityScale = 0.5f;
				BaseCharacter->GetCharacterMovement()->StopMovementImmediately();
			}
			if(!isCustom) SpawnSkillActor(BaseCharacter);
		}
	}
}

template<typename ActorClass>
void USpawnableSkillAnimNotify::SpawnSkillActor(ABaseCharacter* BaseCharacter) const
{
	if (BaseCharacter) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = BaseCharacter;
		FVector SpawnLoc = BaseCharacter->GetSprite()->GetSocketLocation(FName("Eject Point"));
		FRotator SpawnRot = FRotator(0.0f, 0.0f, 0.0f);
		FVector TempAdditionLoc = AdditionalSpawnLoc;
		TempAdditionLoc.X *= (BaseCharacter->GetSprite()->GetForwardVector().X > 0) ? 1 : -1;
		SpawnRot.Yaw = (BaseCharacter->GetSprite()->GetForwardVector().X > 0) ? 0 : 180;
		SpawnRot += AdditionalSpawnRot;
		SpawnLoc += TempAdditionLoc;
		BaseCharacter->GetWorld()->SpawnActor<ActorClass>(ActorClass::StaticClass(), SpawnLoc, SpawnRot, SpawnParams);
	}
}

void USpawnableSkillAnimNotify::SpawnSkillActor(ABaseCharacter* BaseCharacter) const
{
	if (BaseCharacter) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = BaseCharacter;
		FVector SpawnLoc = BaseCharacter->GetSprite()->GetSocketLocation(FName("Eject Point"));
		FRotator SpawnRot = FRotator(0.0f, 0.0f, 0.0f);
		FVector TempAdditionLoc = AdditionalSpawnLoc;
		TempAdditionLoc.X *= (BaseCharacter->GetSprite()->GetForwardVector().X > 0) ? 1 : -1;
		SpawnRot.Yaw = (BaseCharacter->GetSprite()->GetForwardVector().X > 0) ? 0 : 180;
		SpawnRot += AdditionalSpawnRot;
		SpawnLoc += TempAdditionLoc;
		SpawnLoc.Y = 0.0f;
		TSubclassOf<AActor>  TempSubclass = SkillActorSubclass;
		BaseCharacter->GetWorld()->SpawnActor<AActor>(TempSubclass, SpawnLoc, SpawnRot, SpawnParams);
	}
}