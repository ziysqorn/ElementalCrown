// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"
#include "../../Controller/MainController.h"
#include "../../CustomGameInstance/CustomGameInstance.h"

ABossCharacter::ABossCharacter()
{
	MaxHealth = Default_Boss_MaxHealth;
	CurrentHealth = MaxHealth;
	ATK_Damage = Default_Boss_ATKDamage;
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABossCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (canMakeDecision) {
		MakeDecision();
	}
}

float ABossCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!isInvincible) {
		if (CurrentHealth > 0) {
			int FinalDamage = (int)DamageAmount;
			if (UBaseStatusEffect* Effect = StatusEffectComponent->FindStatusEffect("Drowsy")) {
				if (Effect->GetActivateStatus()) {
					FinalDamage = FinalDamage + (int)ceil(MaxHealth * 10.0f / 100.0f);
					StatusEffectComponent->RemoveStatusEffect(Effect);
				}
			}
			if (UBaseStatusEffect* Effect = StatusEffectComponent->FindStatusEffect("Vulnerable")) {
				if (Effect->GetActivateStatus()) FinalDamage = FinalDamage + (int)ceil(MaxHealth * 10.0f / 100.0f);
			}
			if (IGameplayInterface* CauserInteface = Cast<IGameplayInterface>(DamageCauser)) {
				if (UElemental* CauserElemental = CauserInteface->GetElemental()) {
					if (CharacterElement) FinalDamage += (int)ceil(DamageAmount * CharacterElement->CalcDmgByElemental(CauserElemental));
				}
			}
			CurrentHealth -= FinalDamage;
			if (CurrentHealth <= 0) {
				Dead();
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
	}
	return 0.0f;
}

void ABossCharacter::Landed(const FHitResult& Hit)
{
	ABaseCharacter::Landed(Hit);

	FRotator NewRotation = FRotator(0.0f, 180.0f, 0.0f);
	this->SetActorRotation(this->GetActorRotation() + NewRotation);
	GetWorldTimerManager().SetTimer(NewDecisionTimer, FTimerDelegate::CreateUObject(this, &ABossCharacter::SetCanMakeDecision, true), NewDecisionTimeAmount, false);
}


void ABossCharacter::Attack()
{
	attackDecisionMode = FMath::RandRange(1, 3);
	CurrentState = CharacterState::ATTACK;
	switch (attackDecisionMode) {
	case 1:
		GetWorldTimerManager().SetTimer(AttackHandle, FTimerDelegate::CreateUObject(this, &ABossCharacter::SetAttackToNoneState), AttackSequence->GetTotalDuration(), false);
		GetWorldTimerManager().SetTimer(NewDecisionTimer, FTimerDelegate::CreateUObject(this, &ABossCharacter::SetCanMakeDecision, true), AttackSequence->GetTotalDuration() + NewDecisionTimeAmount, false);
		break;
	case 2:
		GetWorldTimerManager().SetTimer(AttackHandle, FTimerDelegate::CreateUObject(this, &ABossCharacter::SetAttackToNoneState), Attack2Sequence->GetTotalDuration(), false);
		GetWorldTimerManager().SetTimer(NewDecisionTimer, FTimerDelegate::CreateUObject(this, &ABossCharacter::SetCanMakeDecision, true), Attack2Sequence->GetTotalDuration() + NewDecisionTimeAmount, false);
		break;
	case 3:
		GetWorldTimerManager().SetTimer(AttackHandle, FTimerDelegate::CreateUObject(this, &ABossCharacter::SetAttackToNoneState), SpecialAtkSequence->GetTotalDuration(), false);
		GetWorldTimerManager().SetTimer(NewDecisionTimer, FTimerDelegate::CreateUObject(this, &ABossCharacter::SetCanMakeDecision, true), SpecialAtkSequence->GetTotalDuration() + NewDecisionTimeAmount, false);
		break;
	}
}

void ABossCharacter::Dead()
{
	StatusEffectComponent->ClearAllStatusEffect();
	GetWorldTimerManager().ClearAllTimersForObject(this);
	CurrentState = CharacterState::DEATH;
	canMakeDecision = false;
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	if (AMainController* MainController = Cast<AMainController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) {
		if (AMainCharacter* MainCharacter = MainController->GetPawn<AMainCharacter>()) {
			MainCharacter->DisableInput(MainController);
			if (UGoldComponent* GoldComponent = MainCharacter->GetGoldComp()) {
				GoldComponent->AddGold(BountyPrice);
			}
			MainCharacter->SaveGameplay();
			MainCharacter->SavePlayerInfo();
			MainCharacter->SaveGameProgress(NextLevelName, FVector(0.0f, 0.0f, 0.0f));
		}
		if (UBossDefeatMessage* BossDefeatMessage = MainController->GetBossDefeatMessage()) {
			BossDefeatMessage->NextLevelName = this->NextLevelName;
			BossDefeatMessage->BossName = this->CharacterName;
			if (UCustomGameInstance* CustomGameInstance = GetWorld()->GetGameInstance<UCustomGameInstance>()) {
				CustomGameInstance->FadeoutBattleTheme();
				CustomGameInstance->PlayBossDefeatSFX();
			}
			MainController->BossDefeatMessageDisplay();
		}
	}
	/*if (DeathSequence) {
		GetWorldTimerManager().SetTimer(DeathHandle, FTimerDelegate::CreateLambda([this]() {
			this->Destroy();
			}), DeathSequence->GetTotalDuration() + 1.50f, false);
	}*/
}

void ABossCharacter::ChangePos()
{
	int BackwardDir = this->GetActorRotation().Yaw == 0.0f ? 1 : -1;
	float LaunchVectorX = abs(LaunchVector.X);
	LaunchVectorX *= BackwardDir;
	/*if (this->GetCharacterState() != CharacterState::STUN)
		this->SetCharacterState(CharacterState::AIRBORNE);*/
	LaunchVector.X = LaunchVectorX;
	this->LaunchCharacter(LaunchVector, true, true);
}

void ABossCharacter::MakeDecision()
{
	if (CurrentState == CharacterState::NONE) {
		int finalDecision = FMath::RandRange(1, 2);
		switch (finalDecision) {
		case 1:
			canMakeDecision = false;
			Attack();
			break;
		case 2:
			canMakeDecision = false;
			ChangePos();
			break;
		}
	}
}

void ABossCharacter::SetAttackToNoneState()
{
	if (CurrentState == CharacterState::ATTACK) CurrentState = CharacterState::NONE;
}
