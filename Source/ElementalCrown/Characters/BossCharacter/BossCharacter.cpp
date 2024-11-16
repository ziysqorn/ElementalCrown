// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"
#include "../../Controller/MainController.h"
#include "../../ElementalCrownGameModeBase.h"

ABossCharacter::ABossCharacter()
{
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupHealthbar();

	MakeDecision();
}

void ABossCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

float ABossCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CurrentHealth > 0) {
		int FinalDamage = (int)DamageAmount;
		if (BaseStatusEffect* Effect = StatusEffectComponent->FindStatusEffect("Drowsy")) {
			if (Effect->GetActivateStatus()) {
				FinalDamage = FinalDamage + (int)ceil(MaxHealth * 10.0f / 100.0f);
				StatusEffectComponent->RemoveStatusEffect(Effect);
			}
		}
		if (BaseStatusEffect* Effect = StatusEffectComponent->FindStatusEffect("Vulnerable")) {
			if (Effect->GetActivateStatus()) FinalDamage = FinalDamage + (int)ceil(MaxHealth * 10.0f / 100.0f);
		}
		CurrentHealth -= FinalDamage;
		if (CurrentHealth <= 0) {
			StatusEffectComponent->ClearAllStatusEffect();
			CurrentState = CharacterState::DEATH;
			GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
			GetWorldTimerManager().ClearAllTimersForObject(this);

			if (AMainController* MainController = Cast<AMainController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) {
				if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
					MainHUD->RemoveBossHealthbarFromBox();
				}
			}

			if (DeathSequence) {
				GetWorldTimerManager().SetTimer(DeathHandle, FTimerDelegate::CreateLambda([this]() {
					this->Destroy();
					}), DeathSequence->GetTotalDuration() + 1.50f, false);
			}
		}
		else {
			/*if (CurrentState != CharacterState::ATTACK && CurrentState != CharacterState::HURT && CurrentState != CharacterState::STUN && CurrentState != CharacterState::AIRBORNE) {
				ABaseStatus* StatusEffect = Cast<ABaseStatus>(DamageCauser);
				if (!StatusEffect) CurrentState = CharacterState::HURT;
			}*/
			FlashTimeline.PlayFromStart();
			/*if (HurtSequence) {
				GetWorldTimerManager().SetTimer(HurtHandle, FTimerDelegate::CreateLambda([this]() {
					if (this->CurrentState == CharacterState::HURT)
						this->CurrentState = CharacterState::NONE;
					}), HurtSequence->GetTotalDuration(), false);
			}*/
		}
		if (StatsPopoutSubclass) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			if (AStatsPopout* stats = GetWorld()->SpawnActor<AStatsPopout>(StatsPopoutSubclass, this->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnParams)) {
				if (UStatsPopoutUI* statsUI = stats->GetStatsPopoutUI()) {
					FText inText = FText::FromString(FString::FromInt(FinalDamage));
					statsUI->SetText(inText);
				}
			}
		}
	}
	return 0.0f;
}

void ABossCharacter::Landed(const FHitResult& Hit)
{
	ABaseCharacter::Landed(Hit);

	FRotator NewRotation = FRotator(0.0f, 180.0f, 0.0f);
	this->SetActorRotation(this->GetActorRotation() + NewRotation);
	GetWorldTimerManager().SetTimer(NewDecisionTimer, FTimerDelegate::CreateLambda([this]() {
		MakeDecision();
		}), NewDecisionTimeAmount, false);
}


void ABossCharacter::Attack()
{
	attackDecisionMode = FMath::RandRange(1, 3);
	CurrentState = CharacterState::ATTACK;
	switch (attackDecisionMode) {
	case 1:
		GetWorldTimerManager().SetTimer(AttackHandle, FTimerDelegate::CreateLambda([this]() {
			if (CurrentState == CharacterState::ATTACK) CurrentState = CharacterState::NONE;
			}), AttackSequence->GetTotalDuration(), false);
		GetWorldTimerManager().SetTimer(NewDecisionTimer, FTimerDelegate::CreateLambda([this]() {
			MakeDecision();
			}), AttackSequence->GetTotalDuration() + NewDecisionTimeAmount, false);
		break;
	case 2:
		GetWorldTimerManager().SetTimer(AttackHandle, FTimerDelegate::CreateLambda([this]() {
			if (CurrentState == CharacterState::ATTACK) CurrentState = CharacterState::NONE;
			}), Attack2Sequence->GetTotalDuration(), false);
		GetWorldTimerManager().SetTimer(NewDecisionTimer, FTimerDelegate::CreateLambda([this]() {
			MakeDecision();
			}), Attack2Sequence->GetTotalDuration() + NewDecisionTimeAmount, false);
		break;
	case 3:
		GetWorldTimerManager().SetTimer(AttackHandle, FTimerDelegate::CreateLambda([this]() {
			if (CurrentState == CharacterState::ATTACK) CurrentState = CharacterState::NONE;
			}), SpecialAtkSequence->GetTotalDuration(), false);
		GetWorldTimerManager().SetTimer(NewDecisionTimer, FTimerDelegate::CreateLambda([this]() {
			MakeDecision();
			}), SpecialAtkSequence->GetTotalDuration() + NewDecisionTimeAmount, false);
		break;
	}
}

void ABossCharacter::ChangePos()
{
	FVector LaunchVector = FVector(600.0f, 0.0f, 500.0f);
	int BackwardDir = this->GetActorRotation().Yaw == 0.0f ? 1 : -1;
	LaunchVector.X *= BackwardDir;
	/*if (this->GetCharacterState() != CharacterState::STUN)
		this->SetCharacterState(CharacterState::AIRBORNE);*/
	this->LaunchCharacter(LaunchVector, true, true);
}

void ABossCharacter::MakeDecision()
{
	if (CurrentState == CharacterState::NONE) {
		int finalDecision = FMath::RandRange(1, 2);
		switch (finalDecision) {
		case 1:
			Attack();
			break;
		case 2:
			ChangePos();
			break;
		}
	}
}

void ABossCharacter::SetupHealthbar()
{
	if (AMainController* MainController = Cast<AMainController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) {
		if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
			if (UBossHealthBar* BossHealthbar = MainHUD->AddBossHealthbarToBox()) {
				BossHealthbar->SetBossName(FText::FromString(CharacterName.ToString()));
				BossHealthbar->SetDelegateForHealthBar(this, FName("GetHealthPercentage"));
			}
		}
	}
}
