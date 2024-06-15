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
	//
	EnemyHealthBar = CreateDefaultSubobject<UWidgetComponent>("Health Bar");
	EnemyHealthBar->SetupAttachment(RootComponent);
	EnemyHealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	EnemyHealthBar->SetDrawAtDesiredSize(true);
}

ABaseEnemyCharacter::~ABaseEnemyCharacter()
{
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	ABaseCharacter::BeginPlay();
}

void ABaseEnemyCharacter::Tick(float DeltaSeconds)
{
	ABaseCharacter::Tick(DeltaSeconds);
	if (!DetectingPlayer() && !DetectingWall()) {
		this->Move();
	}
}

float ABaseEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CurrentHealth > 0) {
		CurrentHealth -= (int)DamageAmount;
		if (CurrentHealth <= 0) {
			CurrentState = CharacterState::DEATH;
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
				if (CurrentState != CharacterState::ATTACK && CurrentState != CharacterState::HURT) {
					CurrentState = CharacterState::HURT;
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
					FText inText = FText::FromString(FString::FromInt((int)DamageAmount));
					statsUI->SetText(inText);
				}
			}
		}
	}
	return 0.0f;
}

void ABaseEnemyCharacter::Landed(const FHitResult& Hit)
{
	GetWorldTimerManager().SetTimer(StunHandle, FTimerDelegate::CreateLambda([this]() {
		if (CurrentState == CharacterState::STUNNED) {
			CurrentState = CharacterState::NONE;
		}
	}), 0.750f, false);
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
	FVector WallDetectBoxExtent(20, 0, 40);
	FVector BoxPosition(20 * GetSprite()->GetForwardVector().X, 0, 0);
	bool WallDetected{ GetWorld()->SweepSingleByObjectType(WallDetectResult, this->GetActorLocation() + BoxPosition, this->GetActorLocation() + BoxPosition, FQuat(0, 0, 0, 0), FCollisionObjectQueryParams::AllStaticObjects, FCollisionShape::MakeBox(WallDetectBoxExtent)) };
	DrawDebugBox(GetWorld(), this->GetActorLocation() + BoxPosition, WallDetectBoxExtent, FColor::Red);
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
