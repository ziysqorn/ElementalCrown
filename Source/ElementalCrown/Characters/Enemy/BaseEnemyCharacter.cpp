// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacter.h"

ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	//Stats setup
	DeStun = Default_Enemy_DeStun;
	MaxMana = -1;
	CurrentMana = MaxMana;
	//CharacterMovement setup
	GetCharacterMovement()->MaxWalkSpeed = BaseEnemySpeed;
	//Setup enemy health bar component
	EnemyHealthBar = CreateDefaultSubobject<UWidgetComponent>("Health Bar");
	EnemyHealthBar->SetupAttachment(RootComponent);
	EnemyHealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	EnemyHealthBar->SetDrawAtDesiredSize(true);
	//
	
}

ABaseEnemyCharacter::~ABaseEnemyCharacter()
{
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	ABaseCharacter::BeginPlay();
	if (UUserWidget* widget = EnemyHealthBar->GetUserWidgetObject()) {
		if (UEnemyHealthBar* healthBar = Cast<UEnemyHealthBar>(widget)) {
			healthBar->SetDelegateForHealthBar(this, FName("GetHealthPercentage"));
		}
	}
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
}

void ABaseEnemyCharacter::Tick(float DeltaSeconds)
{
	ABaseCharacter::Tick(DeltaSeconds);
	if (!DetectingPlayer() && !DetectingWall()) this->Move();
	else if (DetectingPlayer()) this->Attack();
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
		CurrentHealth -= FinalDamage;
		if (CurrentHealth <= 0) {
			StatusEffectComponent->ClearAllStatusEffect();
			CurrentState = CharacterState::DEATH;
			GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
			GetWorldTimerManager().ClearAllTimersForObject(this);
			if (DeathSequence) {
				GetWorldTimerManager().SetTimer(DeathHandle, FTimerDelegate::CreateLambda([this]() {
					this->Destroy();
					}), DeathSequence->GetTotalDuration() + 1.50f, false);
			}
		}
		else {
			FlashTimeline.PlayFromStart();
			if (HurtSequence) {
				if (CurrentState != CharacterState::ATTACK && CurrentState != CharacterState::HURT && CurrentState != CharacterState::STUN) {
					ABaseStatus* StatusEffect = Cast<ABaseStatus>(DamageCauser);
					if (!StatusEffect) CurrentState = CharacterState::HURT;
				}
				GetWorldTimerManager().SetTimer(HurtHandle, FTimerDelegate::CreateLambda([this, EventInstigator]() {
					if (this->CurrentState == CharacterState::HURT) {
						this->CurrentState = CharacterState::NONE;
					}
					if (EventInstigator) {
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

void ABaseEnemyCharacter::Landed(const FHitResult& Hit)
{
}

void ABaseEnemyCharacter::Move()
{
	if (CurrentState == CharacterState::NONE)
	AddMovementInput(GetSprite()->GetForwardVector());
}

void ABaseEnemyCharacter::Attack()
{
	if (CurrentState == CharacterState::NONE && AttackRecovered) {
		CurrentState = CharacterState::ATTACK;
		AttackRecovered = false; 
		if (AttackSequence) {
			GetWorldTimerManager().SetTimer(AttackHandle, FTimerDelegate::CreateLambda([this]() {
				if(CurrentState == CharacterState::ATTACK)
				this->CurrentState = CharacterState::NONE;
				}), AttackSequence->GetTotalDuration(), false);
		}
		GetWorldTimerManager().SetTimer(AttackRecoverHandle, FTimerDelegate::CreateLambda([this]() {
			this->AttackRecovered = true;
		}), AttackSpeed, false);
	}
}

bool ABaseEnemyCharacter::DetectingPlayer()
{
	FHitResult PlayerDetectResult;
	FCollisionObjectQueryParams DetectObjectsParams(ECollisionChannel::ECC_Pawn);
	FCollisionQueryParams DetectParams;
	DetectParams.AddIgnoredActor(this);
	DrawDebugBox(GetWorld(), this->GetActorLocation(), PlayerDetectBox, FColor::Blue);
	bool PlayerDetected{ GetWorld()->SweepSingleByObjectType(PlayerDetectResult, this->GetActorLocation(), this->GetActorLocation(), FQuat(0, 0, 0, 0), DetectObjectsParams, FCollisionShape::MakeBox(PlayerDetectBox), DetectParams) };
	if (PlayerDetected) {
		FRotator CharacterRotation = (PlayerDetectResult.GetActor()->GetActorLocation().X > this->GetActorLocation().X) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
		if (abs(PlayerDetectResult.GetActor()->GetActorLocation().X - this->GetActorLocation().X)>=30 && CurrentState != CharacterState::HURT && CurrentState != CharacterState::DEATH && CurrentState != CharacterState::ATTACK)
			this->SetActorRotation(CharacterRotation);
		return abs(PlayerDetectResult.GetActor()->GetActorLocation().X - this->GetActorLocation().X) <= 50;
	}
	return false;
}

bool ABaseEnemyCharacter::DetectingWall()
{
	FHitResult WallDetectResult;
	FVector BoxPosition(20 * GetSprite()->GetForwardVector().X, 0, 0);
	bool WallDetected{ GetWorld()->SweepSingleByObjectType(WallDetectResult, this->GetActorLocation() + BoxPosition, this->GetActorLocation() + BoxPosition, FQuat(0, 0, 0, 0), FCollisionObjectQueryParams::AllStaticObjects, FCollisionShape::MakeBox(WallDetectBox)) };
	DrawDebugBox(GetWorld(), this->GetActorLocation() + BoxPosition, WallDetectBox, FColor::Red);
	if (WallDetected) {
		FRotator CharacterRotation = (WallDetectResult.Location.X > this->GetActorLocation().X) ? FRotator(0, 180, 0) : FRotator(0, 0, 0);
		if (!GetWorldTimerManager().IsTimerActive(TurnBackHandle)) {
			GetWorldTimerManager().SetTimer(TurnBackHandle, FTimerDelegate::CreateLambda([this, CharacterRotation]() {
				this->SetActorRotation(CharacterRotation);
				}), 3, false);
		}
	}
	return WallDetected;
}
