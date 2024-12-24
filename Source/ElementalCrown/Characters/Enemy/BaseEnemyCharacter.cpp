// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacter.h"
#include "../Main Character/MainCharacter.h"

ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	MaxMana = -1;
	CurrentMana = MaxMana;

	MaxHealth = 40;
	CurrentHealth = MaxHealth;

	ATK_Damage = 6;
	//CharacterMovement setup
	GetCharacterMovement()->MaxWalkSpeed = BaseEnemySpeed;
	//Setup enemy health bar component
	EnemyHealthBar = CreateDefaultSubobject<UWidgetComponent>("Health Bar");
	EnemyHealthBar->SetupAttachment(RootComponent);
	EnemyHealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	EnemyHealthBar->SetDrawAtDesiredSize(false);
	//
	
}

ABaseEnemyCharacter::~ABaseEnemyCharacter()
{
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (UUserWidget* widget = EnemyHealthBar->GetUserWidgetObject()) {
		if (UEnemyHealthBar* healthBar = Cast<UEnemyHealthBar>(widget)) {
			healthBar->SetDelegateForHealthBar(this, FName("GetHealthPercentage"));
		}
	}
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ABaseEnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (isMovingAllowed && !DetectingEdge() && !DetectingPatrolLimit() && !DetectingPlayer()) this->Move();
	else if (DetectingPlayer() && AttackRecovered) this->Attack();
}

float ABaseEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
		if (IGameplayInterface* CauserInteface = Cast<IGameplayInterface>(DamageCauser)) {
			if (UElemental* CauserElemental = CauserInteface->GetElemental()) {
				if (CharacterElement) FinalDamage += (int)ceil(DamageAmount * CharacterElement->CalcDmgByElemental(CauserElemental));
			}
		}
		CurrentHealth -= FinalDamage;
		if (CurrentHealth <= 0) {
			this->Dead();
		}
		else {
			FlashTimeline.PlayFromStart();
			if (HurtSequence) {
				if (CurrentState != CharacterState::ATTACK && CurrentState != CharacterState::HURT && CurrentState != CharacterState::STUN && CurrentState != CharacterState::AIRBORNE) {
					ABaseStatus* StatusEffect = Cast<ABaseStatus>(DamageCauser);
					if (!StatusEffect) CurrentState = CharacterState::HURT;
				}
				GetWorldTimerManager().SetTimer(HurtHandle, FTimerDelegate::CreateLambda([this, EventInstigator]() {
					if (this->CurrentState == CharacterState::HURT) {
						this->CurrentState = CharacterState::NONE;
					}
					if (EventInstigator && EventInstigator->GetPawn()) {
						FRotator CharacterRotation = (EventInstigator->GetPawn()->GetActorLocation().X > this->GetActorLocation().X) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
						this->SetActorRotation(CharacterRotation);
					}
					}), HurtSequence->GetTotalDuration(), false);
			}
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

void ABaseEnemyCharacter::Move()
{
	if (CurrentState == CharacterState::NONE)
	AddMovementInput(GetSprite()->GetForwardVector());
}

void ABaseEnemyCharacter::Attack()
{
	if (CurrentState == CharacterState::NONE) {
		CurrentState = CharacterState::ATTACK;
		AttackRecovered = false; 
		if (AttackSequence) {
			GetWorldTimerManager().SetTimer(AttackHandle, FTimerDelegate::CreateLambda([this]() {
				if(CurrentState == CharacterState::ATTACK)
				this->CurrentState = CharacterState::NONE;
				}), AttackSequence->GetTotalDuration(), false);
			GetWorldTimerManager().SetTimer(AttackRecoverHandle, FTimerDelegate::CreateLambda([this]() {
				this->AttackRecovered = true;
				}), AttackSequence->GetTotalDuration() + AttackSpeed, false);
		}
	}
}

void ABaseEnemyCharacter::Dead()
{
	StatusEffectComponent->ClearAllStatusEffect();
	CurrentState = CharacterState::DEATH;
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
		if (AMainCharacter* MainCharacter = PlayerController->GetPawn<AMainCharacter>()) {
			if (UGoldComponent* GoldComponent = MainCharacter->GetGoldComp()) {
				int randomPrice = FMath::RandRange(6, maxBountyPrice);
				GoldComponent->AddGold(randomPrice);
			}
		}
	}
	if (DeathSequence) {
		GetWorldTimerManager().SetTimer(DeathHandle, FTimerDelegate::CreateLambda([this]() {
			this->Destroy();
			}), DeathSequence->GetTotalDuration() + 1.50f, false);
	}
}

void ABaseEnemyCharacter::TurnBackAfterTime()
{
	if (!GetWorldTimerManager().IsTimerActive(TurnBackHandle)) {
		GetWorldTimerManager().SetTimer(TurnBackHandle, FTimerDelegate::CreateUObject(this, &ABaseEnemyCharacter::TurnBackImmediate), 3.0f, false);
	}
}

void ABaseEnemyCharacter::TurnBackImmediate()
{
	this->SetActorRotation(this->GetActorRotation() + FRotator(0.0f, 180.0f, 0.0f));
	isMovingAllowed = true;
}

bool ABaseEnemyCharacter::DetectingPlayer()
{
	FHitResult PlayerDetectResult;
	FCollisionObjectQueryParams DetectObjectsParams(ECollisionChannel::ECC_Pawn);
	FCollisionQueryParams DetectParams;
	DetectParams.AddIgnoredActor(this);
	//DrawDebugBox(GetWorld(), this->GetActorLocation() + PlayerDetectBoxPos, PlayerDetectBox, FColor::Blue);
	bool PlayerDetected = GetWorld()->SweepSingleByObjectType(PlayerDetectResult, this->GetActorLocation() + PlayerDetectBoxPos, this->GetActorLocation() + PlayerDetectBoxPos, FQuat(0, 0, 0, 0), DetectObjectsParams, FCollisionShape::MakeBox(PlayerDetectBox), DetectParams);
	if (PlayerDetected) {
		FRotator CharacterRotation = (PlayerDetectResult.GetActor()->GetActorLocation().X > this->GetActorLocation().X) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
		ABaseEnemyCharacter* Enemy = Cast<ABaseEnemyCharacter>(PlayerDetectResult.GetActor());
		if (!Enemy) {
			if (GetWorldTimerManager().IsTimerActive(TurnBackHandle)) GetWorldTimerManager().ClearTimer(TurnBackHandle);
			if (abs(PlayerDetectResult.GetActor()->GetActorLocation().X - this->GetActorLocation().X) >= 30 && CurrentState != CharacterState::HURT && CurrentState != CharacterState::DEATH && CurrentState != CharacterState::ATTACK)
				this->SetActorRotation(CharacterRotation);
			return abs(PlayerDetectResult.GetActor()->GetActorLocation().X - this->GetActorLocation().X) <= AttackTriggerDistanceX;
		}
	}
	return false;
}

bool ABaseEnemyCharacter::DetectingPatrolLimit()
{
	FHitResult PatrolLimitDetectedResult;
	FVector BoxPosition(20 * GetSprite()->GetForwardVector().X, 0, 0);
	FCollisionObjectQueryParams ObjectLookingFor;
	ObjectLookingFor.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	ObjectLookingFor.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel3);
	bool PatrolLimitDetected = GetWorld()->SweepSingleByObjectType(PatrolLimitDetectedResult, this->GetActorLocation() + BoxPosition, this->GetActorLocation() + BoxPosition, FQuat(0, 0, 0, 0), ObjectLookingFor, FCollisionShape::MakeBox(WallDetectBox));
	//DrawDebugBox(GetWorld(), this->GetActorLocation() + BoxPosition, WallDetectBox, FColor::Red);
	if (PatrolLimitDetected) TurnBackAfterTime();
	return PatrolLimitDetected;
}

bool ABaseEnemyCharacter::DetectingEdge()
{
	FHitResult EdgeDetectResult;
	FVector TempStartPoint = EdgeDetectStartPoint;
	TempStartPoint.X *= GetSprite()->GetForwardVector().X;
	FVector StartPoint = this->GetActorLocation() + TempStartPoint;
	float DistanceToGround = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	FVector EndPoint = StartPoint - FVector(0.0f, 0.0f, DistanceToGround + 20.0f);
	FCollisionObjectQueryParams ObjectLookingFor;
	ObjectLookingFor.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	bool GroundDetected = GetWorld()->LineTraceSingleByObjectType(EdgeDetectResult, StartPoint, EndPoint, ObjectLookingFor);
	if (!GroundDetected) TurnBackAfterTime();
	return !GroundDetected;
}
