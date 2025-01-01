// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "../../Controller/MainController.h"
#include "../../Interface/InteractableInterface.h"
#include "../../CustomStructures/SkillData.h"
#include "../../CustomStructures/ConsumableData.h"
#include "../../CustomSave/GameplaySave.h"
#include "../../CustomSave/PlayerInfoSave.h"
#include "../../CustomSave/GameProgress.h"

AMainCharacter::AMainCharacter()
{
	//Components setup
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	GoldComponent = CreateDefaultSubobject<UGoldComponent>(TEXT("GoldComponent"));
	PaperTileMapComp = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("PaperTileMapComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
	PaperTileMapComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
	ConsumableComponent = CreateDefaultSubobject<UConsumableComponent>(TEXT("ConsumableComponent"));
	//Character movement
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;
	GetCharacterMovement()->MaxFlySpeed = RunSpeed;
	GetCharacterMovement()->AirControl = 0.75;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	
}

AMainCharacter::~AMainCharacter()
{
}

void AMainCharacter::BeginPlay()
{

	Super::BeginPlay();

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

}

void AMainCharacter::Tick(float DeltaSeconds)
{
	ABaseCharacter::Tick(DeltaSeconds);
}

float AMainCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
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
		CurrentHealth -= FinalDamage;
		if (CurrentHealth <= 0) {
			this->Dead();
		}
		else {
			if (CurrentState != CharacterState::ATTACK && CurrentState != CharacterState::HURT && CurrentState != CharacterState::STUN && CurrentState != CharacterState::AIRBORNE) {
				ABaseStatus* StatusEffect = Cast<ABaseStatus>(DamageCauser);
				if (!StatusEffect) {
					CurrentState = CharacterState::HURT;
					if (HurtSFX) UGameplayStatics::PlaySound2D(this, HurtSFX);
				}
			}
			FlashTimeline.PlayFromStart();
			if (HurtSequence) {
				GetWorldTimerManager().SetTimer(HurtHandle, FTimerDelegate::CreateLambda([this]() {
					if (this->CurrentState == CharacterState::HURT)
						this->CurrentState = CharacterState::NONE;
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

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EIComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		if (AMainController* MainController = Cast<AMainController>(GetController())) {
			EIComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
			EIComponent->BindAction(IA_Move, ETriggerEvent::Completed, this, &AMainCharacter::StopMoving);
			EIComponent->BindAction(IA_Dodge, ETriggerEvent::Triggered, this, &AMainCharacter::Dodge);
			EIComponent->BindAction(IA_UseSkill, ETriggerEvent::Triggered, this, &AMainCharacter::UseSkill);
			EIComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AMainCharacter::CustomJump);
			EIComponent->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &AMainCharacter::Attack);
			EIComponent->BindAction(IA_Shoot, ETriggerEvent::Triggered, this, &AMainCharacter::Shoot);
			EIComponent->BindAction(IA_ChangeSkill, ETriggerEvent::Triggered, this, &AMainCharacter::ChangeSkill);
			EIComponent->BindAction(IA_UseHealPot, ETriggerEvent::Triggered, ConsumableComponent, &UConsumableComponent::UsePotion, 0);
			EIComponent->BindAction(IA_UseManaPot, ETriggerEvent::Triggered, ConsumableComponent, &UConsumableComponent::UsePotion, 1);
			EIComponent->BindAction(IA_UseBleedCurePot, ETriggerEvent::Triggered, ConsumableComponent, &UConsumableComponent::UsePotion, 2);
			EIComponent->BindAction(IA_UseBurnCurePot, ETriggerEvent::Triggered, ConsumableComponent, &UConsumableComponent::UsePotion, 3);
			EIComponent->BindAction(IA_UseDrowsyCurePot, ETriggerEvent::Triggered, ConsumableComponent, &UConsumableComponent::UsePotion, 4);
			EIComponent->BindAction(IA_UseStunCurePot, ETriggerEvent::Triggered, ConsumableComponent, &UConsumableComponent::UsePotion, 5);
			EIComponent->BindAction(IA_UseVulnerableCurePot, ETriggerEvent::Triggered, ConsumableComponent, &UConsumableComponent::UsePotion, 6);
			EIComponent->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &AMainCharacter::Interact);
			EIComponent->BindAction(IA_PauseGame, ETriggerEvent::Triggered, MainController, &AMainController::PauseGame);
		}
	}
}

void AMainCharacter::SetupMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(MainMappingContext, 0);
		}
	}
	
}

void AMainCharacter::Move(const FInputActionValue& value)
{
	//CurrentState != CharacterState::ATTACK && CurrentState != CharacterState::SLIDE && CurrentState != CharacterState::SHOOT && CurrentState != CharacterState::DODGE && CurrentState != CharacterState::USESKILL
	if (CurrentState == CharacterState::NONE) {
		const float DirectionValue = value.Get<float>();
		if (this->GetController() && DirectionValue != 0) {
			//Wall slide implementation
			bool HitWall = GetWorld()->LineTraceTestByObjectType(this->GetActorLocation(), this->GetActorLocation() + FVector(25, 0, 0) * GetSprite()->GetForwardVector(), FCollisionObjectQueryParams::AllStaticObjects);
			bool HitWallReversed = GetWorld()->LineTraceTestByObjectType(this->GetActorLocation(), this->GetActorLocation() + FVector(23, 0, 0) * GetSprite()->GetForwardVector() * -1, FCollisionObjectQueryParams::AllStaticObjects);
			if (WallSliding = (HitWall || HitWallReversed) && this->GetVelocity().Z < 0) {
				if (this->GetCharacterMovement()->GravityScale == 1) {
					GetCharacterMovement()->StopMovementImmediately();
					this->GetCharacterMovement()->GravityScale = 0.1;
				}
			}
			else {
				if (this->GetCharacterMovement()->GravityScale < 1) {
					this->GetCharacterMovement()->GravityScale = 1;
				}
			}

			//Move the character
			AddMovementInput(FVector(1, 0, 0), DirectionValue);

			//Rotate the character
			if (this->GetVelocity().Z == 0 || WallSliding) {
				if (DirectionValue > 0) {
					GetController()->SetControlRotation(FRotator(0, 0, 0));
				}
				else {
					GetController()->SetControlRotation(FRotator(0, 180, 0));
				}
			}
		}
		if (isSwordSheathed == false) {
			GetWorldTimerManager().SetTimer(SheatheSwordHandle, this, &AMainCharacter::SheatheSword, 3, false);
		}
	}
}

void AMainCharacter::StopMoving()
{
	if (this->GetCharacterMovement()->GravityScale < 1) {
		this->GetCharacterMovement()->GravityScale = 1;
	}
}


void AMainCharacter::Dodge()
{
	if (GetVelocity().Z == 0.0f && CurrentState == CharacterState::NONE && canDodge) {
		CurrentState = CharacterState::DODGE;
		int ForwardDir = this->GetActorRotation().Yaw == 0.0f ? 1 : -1;
		this->LaunchCharacter(FVector(1000.0f * ForwardDir, 0.0f, 0.0f), true, false);
		canDodge = false;
		GetCharacterMovement()->GravityScale = 0.0f;
		GetCapsuleComponent()->SetCollisionObjectType(ECC_GameTraceChannel2);
		GetWorld()->SpawnActor<ASmoke>(RunSmokeSubclass, GetSprite()->GetSocketLocation(FName("RunSmoke")), GetSprite()->GetSocketRotation(FName("RunSmoke")));
		this->GetWorldTimerManager().SetTimer(DodgeHandle, FTimerDelegate::CreateLambda([this]() {
			if (this) {
				if (CurrentState == CharacterState::DODGE) {
					CurrentState = CharacterState::NONE;
					GetCapsuleComponent()->SetCollisionObjectType(ECC_Pawn);
					GetCharacterMovement()->GravityScale = 1.0f;
				}
			}
			}), 0.35f, false);
		this->GetWorldTimerManager().SetTimer(DodgeEnableHandle, FTimerDelegate::CreateLambda([this]() {
			if (this) {
				if (!canDodge) canDodge = true;
			}
			}), 1.0f, false);
	}
}


void AMainCharacter::CustomJump()
{
	if (CurrentState == CharacterState::NONE) {
		if (WallSliding) {
			if (this->GetCharacterMovement()->MaxWalkSpeed == RunSpeed) {
				GetCharacterMovement()->GroundFriction = 8;
				GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
			}
			this->JumpCurrentCount = 0;
			this->GetCharacterMovement()->AddImpulse(FVector(1000 * GetSprite()->GetForwardVector().X, 0, 600), true);
			if (JumpCurrentCount == 0) {
				if (JumpSFX1) UGameplayStatics::PlaySound2D(this, JumpSFX1);
			}
			else if (JumpCurrentCount == 1) {
				if (JumpSFX2) UGameplayStatics::PlaySound2D(this, JumpSFX2);
			}
		}
		else {
			AMainCharacter::Jump();
			if (JumpCurrentCount == 0) {
				if (JumpSFX1) UGameplayStatics::PlaySound2D(this, JumpSFX1);
			}
			else if (JumpCurrentCount == 1) {
				if (JumpSFX2) UGameplayStatics::PlaySound2D(this, JumpSFX2);
			}
		}
	}
}

void AMainCharacter::Attack()
{
	if (CurrentState == CharacterState::NONE) {
		if (this->GetVelocity().Z == 0) {
			if (attackCounter < 3) {
				if (Slash1 && Slash2 && Slash3) {
					++attackCounter;
					CurrentState = CharacterState::ATTACK;
					isSwordSheathed = false;
					switch (attackCounter) {
					case 1:
						GetWorldTimerManager().SetTimer(AttackHandle, this, &AMainCharacter::EndAttack, Slash1->GetTotalDuration(), false);
						GetWorldTimerManager().SetTimer(ComboHandle, this, &AMainCharacter::EndCombo, Slash1->GetTotalDuration() + 0.3, false);
						GetWorldTimerManager().SetTimer(SheatheSwordHandle, this, &AMainCharacter::SheatheSword, Slash1->GetTotalDuration() + 3, false);
						break;
					case 2:
						GetWorldTimerManager().SetTimer(AttackHandle, this, &AMainCharacter::EndAttack, Slash2->GetTotalDuration(), false);
						GetWorldTimerManager().SetTimer(ComboHandle, this, &AMainCharacter::EndCombo, Slash2->GetTotalDuration() + 0.3, false);
						GetWorldTimerManager().SetTimer(SheatheSwordHandle, this, &AMainCharacter::SheatheSword, Slash2->GetTotalDuration() + 3, false);
						break;
					case 3:
						GetWorldTimerManager().SetTimer(AttackHandle, this, &AMainCharacter::EndAttack, Slash3->GetTotalDuration(), false);
						GetWorldTimerManager().SetTimer(ComboHandle, this, &AMainCharacter::EndCombo, Slash3->GetTotalDuration(), false);
						GetWorldTimerManager().SetTimer(SheatheSwordHandle, this, &AMainCharacter::SheatheSword, Slash3->GetTotalDuration() + 3, false);
						break;
					}
				}
			}
		}
		else {
			if (attackCounter < 3) {
				if (AirSlash1 && AirSlash2 && AirSlash3) {
					++attackCounter;
					CurrentState = CharacterState::ATTACK;
					GetCharacterMovement()->GravityScale = 0.5;
					isSwordSheathed = false;
					switch (attackCounter) {
					case 1:
						GetCharacterMovement()->StopMovementImmediately();
						GetWorldTimerManager().SetTimer(AttackHandle, this, &AMainCharacter::EndAirAttack, AirSlash1->GetTotalDuration(), false);
						GetWorldTimerManager().SetTimer(ComboHandle, this, &AMainCharacter::EndCombo, AirSlash1->GetTotalDuration() + 0.2, false);
						GetWorldTimerManager().SetTimer(SheatheSwordHandle, this, &AMainCharacter::SheatheSword, AirSlash1->GetTotalDuration() + 3, false);
						break;
					case 2:
						GetCharacterMovement()->StopMovementImmediately();
						GetWorldTimerManager().SetTimer(AttackHandle, this, &AMainCharacter::EndAirAttack, AirSlash2->GetTotalDuration(), false);
						GetWorldTimerManager().SetTimer(ComboHandle, this, &AMainCharacter::EndCombo, AirSlash2->GetTotalDuration() + 0.2, false);
						GetWorldTimerManager().SetTimer(SheatheSwordHandle, this, &AMainCharacter::SheatheSword, AirSlash2->GetTotalDuration() + 3, false);
						break;
					case 3:
						GetWorldTimerManager().ClearTimer(ComboHandle);
						GetCharacterMovement()->GravityScale = 6;
						break;
					}
				}
			}
		}
	}
}

void AMainCharacter::Shoot()
{
	if (CurrentState == CharacterState::NONE) {
		CurrentState = CharacterState::SHOOT;
		if (this->GetVelocity().Z == 0) {
			if(BowShoot)
			GetWorldTimerManager().SetTimer(AttackHandle, this, &AMainCharacter::EndAttack, BowShoot->GetTotalDuration(), false);
		}
		else {
			if (JumpShoot) {
				GetCharacterMovement()->GravityScale = 0.5;
				GetCharacterMovement()->StopMovementImmediately();
				GetWorldTimerManager().SetTimer(AttackHandle, this, &AMainCharacter::EndAirAttack, JumpShoot->GetTotalDuration(), false);
			}
		}
	}
}

void AMainCharacter::Dead()
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
	if (DieSFX) UGameplayStatics::PlaySound2D(this, DieSFX);
	if (UPlayerInfoSave* PlayerInfoSave = Cast<UPlayerInfoSave>(UGameplayStatics::LoadGameFromSlot("PlayerInfoSave", 0))) {
		int* SavedHealth = PlayerInfoSave->GetPlayerHealth();
		int* SavedMana = PlayerInfoSave->GetPlayerMana();
		int* SavedGold = PlayerInfoSave->GetCurrentGold();
		int* SavedLiveCount = PlayerInfoSave->GetPlayerLiveCount();
		*SavedHealth = MaxHealth;
		*SavedMana = MaxMana;
		if (GoldComponent) {
			*SavedGold = GoldComponent->GetCurrentGold();
		}
		--LiveCount;
		if (LiveCount >= 0) {
			*SavedLiveCount = LiveCount;
			SaveGameplay();
		}
		else {
			*SavedLiveCount = 1;
			if (GoldComponent) {
				*SavedGold = 0;
			}
			ClearAllSaveGame();
			SaveGameProgress(FName("Jungle1"), FVector(0.0f, 0.0f, 0.0f));
		}
		UGameplayStatics::SaveGameToSlot(PlayerInfoSave, "PlayerInfoSave", 0);
	}
	if (AMainController* MainController = this->GetController<AMainController>()) {
		DisableInput(MainController);
		MainController->DeadMessageDisplay();
		if (DieMessageSFX) UGameplayStatics::PlaySound2D(this, DieMessageSFX);
	}
	StatusEffectComponent->ClearAllStatusEffect();
	CurrentState = CharacterState::DEATH;
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	/*if (DeathSequence) {
		GetWorldTimerManager().SetTimer(DeathHandle, FTimerDelegate::CreateLambda([this]() {
			this->Destroy();
			}), DeathSequence->GetTotalDuration() + 1.50f, false);
	}*/
}

void AMainCharacter::UseSkill()
{
	if (CurrentState == CharacterState :: NONE) SkillComponent->UseSkill();
}


void AMainCharacter::ChangeSkill()
{
	SkillComponent->ChangeSkill();
}

void AMainCharacter::Interact()
{
	TArray<AActor*> actors; 
	this->GetOverlappingActors(actors, AActor::StaticClass());
	for (int i = 0; i < actors.Num(); ++i) {
		if (IInteractableInterface* InteractableInterface = Cast<IInteractableInterface>(actors[i])) {
			InteractableInterface->Interact(this);
			break;
		}
	}
}

void AMainCharacter::LoadGameplayFromSave()
{
	if (SkillComponent) SkillComponent->LoadSkill();
	if (ConsumableComponent) ConsumableComponent->LoadConsumable();
}

void AMainCharacter::LoadInfoFromSave()
{
	if (UGameplayStatics::DoesSaveGameExist("PlayerInfoSave", 0)) {
		if (UPlayerInfoSave* PlayerInfoSave = Cast<UPlayerInfoSave>(UGameplayStatics::LoadGameFromSlot("PlayerInfoSave", 0))) {
			CurrentHealth = *PlayerInfoSave->GetPlayerHealth();
			CurrentMana = *PlayerInfoSave->GetPlayerMana();
			LiveCount = *PlayerInfoSave->GetPlayerLiveCount();
			if (GoldComponent) {
				GoldComponent->SetCurrentGold((*PlayerInfoSave->GetCurrentGold()));
			}
		}
	}
	else if (UPlayerInfoSave* PlayerInfoSave = Cast<UPlayerInfoSave>(UGameplayStatics::CreateSaveGameObject(UPlayerInfoSave::StaticClass()))) {
		if (GoldComponent) {
			int* SavedGold = PlayerInfoSave->GetCurrentGold();
			int* SavedHealth = PlayerInfoSave->GetPlayerHealth();
			int* SavedMana = PlayerInfoSave->GetPlayerMana();
			int* SavedLiveCount = PlayerInfoSave->GetPlayerLiveCount();
			*SavedGold = GoldComponent->GetCurrentGold();
			*SavedHealth = MaxHealth;
			*SavedMana = MaxMana;
			*SavedLiveCount = LiveCount;
			UGameplayStatics::SaveGameToSlot(PlayerInfoSave, "PlayerInfoSave", 0);
		}
	}
}

void AMainCharacter::SaveGameplay()
{
	if (UGameplayStatics::DoesSaveGameExist("GameplaySave", 0)) {
		if (UGameplaySave* GameplaySave = Cast<UGameplaySave>(UGameplayStatics::LoadGameFromSlot("GameplaySave", 0))) {
			TArray<FName>& SavedConsumable = GameplaySave->GetConsumableList();
			TArray<int>& SavedConsumableQuant = GameplaySave->GetConsumableQuantList();
			if (ConsumableComponent) {
				TArray<UConsumable*>& ConsumableList = ConsumableComponent->GetConsumableList();
				for (int i = 0; i < ConsumableList.Num(); ++i) {
					FString ConsumableNameString = ConsumableList[i]->GetConsumableName().ToString().Replace(TEXT(" "), TEXT(""));
					SavedConsumable[i] = FName(ConsumableNameString);
					SavedConsumableQuant[i] = (*ConsumableList[i]->GetCurrentQuant());
				}
			}
			TArray<FName>& SavedOwnedSkillList = GameplaySave->GetOwnedSkills();
			TArray<int>& SavedEquippedSkillIdxList = GameplaySave->GetEquippedSkillIdxList();
			SavedOwnedSkillList.Empty();
			SavedEquippedSkillIdxList.Empty();
			if (SkillComponent) {
				TArray<UBaseSkill*>& OwnedSkillList = *SkillComponent->GetOwnedSkillList();
				TArray<UBaseSkill*>& SkillList = *SkillComponent->GetSkillList();
				SavedOwnedSkillList.Init(FName(""), OwnedSkillList.Num());
				SavedEquippedSkillIdxList.Init(-1, OwnedSkillList.Num());
				for (int i = 0; i < OwnedSkillList.Num(); ++i) {
					FString SkillNameStr = OwnedSkillList[i]->GetSkillName().ToString().Replace(TEXT(" "), TEXT(""));
					SavedOwnedSkillList[i] = FName(SkillNameStr);
				}
				for (int i = 0; i < SkillList.Num(); ++i) {
					FString SkillNameStr = SkillList[i]->GetSkillName().ToString().Replace(TEXT(" "), TEXT(""));
					int idx = SavedOwnedSkillList.Find(FName(SkillNameStr));
					if (idx != INDEX_NONE) {
						SavedEquippedSkillIdxList[idx] = i;
					}
				}

			}
			UGameplayStatics::SaveGameToSlot(GameplaySave, "GameplaySave", 0);
		}
	}
	else {
		if (UGameplaySave* GameplaySave = Cast<UGameplaySave>(UGameplayStatics::CreateSaveGameObject(UGameplaySave::StaticClass()))) {
			TArray<FName>& SavedConsumable = GameplaySave->GetConsumableList();
			TArray<int>& SavedConsumableQuant = GameplaySave->GetConsumableQuantList();
			if (ConsumableComponent) {
				TArray<UConsumable*>& ConsumableList = ConsumableComponent->GetConsumableList();
				for (int i = 0; i < ConsumableList.Num(); ++i) {
					FString ConsumableNameString = ConsumableList[i]->GetConsumableName().ToString().Replace(TEXT(" "), TEXT(""));
					SavedConsumable.Add(FName(ConsumableNameString));
					SavedConsumableQuant.Add((*ConsumableList[i]->GetCurrentQuant()));
				}
			}
			TArray<FName>& SavedOwnedSkillList = GameplaySave->GetOwnedSkills();
			TArray<int>& SavedEquippedSkillIdxList = GameplaySave->GetEquippedSkillIdxList();
			UGameplayStatics::SaveGameToSlot(GameplaySave, "GameplaySave", 0);
		}
	}
}

void AMainCharacter::SavePlayerInfo()
{
	if (UGameplayStatics::DoesSaveGameExist("PlayerInfoSave", 0)) {
		if (UPlayerInfoSave* PlayerInfoSave = Cast<UPlayerInfoSave>(UGameplayStatics::LoadGameFromSlot("PlayerInfoSave", 0))) {
			int* SavedGold = PlayerInfoSave->GetCurrentGold();
			int* SavedHealth = PlayerInfoSave->GetPlayerHealth();
			int* SavedMana = PlayerInfoSave->GetPlayerMana();
			int* SavedLiveCount = PlayerInfoSave->GetPlayerLiveCount();
			*SavedHealth = (int)this->GetCurrentHealth();
			*SavedMana = this->GetCurrentMana();
			*SavedLiveCount = LiveCount;
			if (GoldComponent) {
				*SavedGold = GoldComponent->GetCurrentGold();
			}
			UGameplayStatics::SaveGameToSlot(PlayerInfoSave, "PlayerInfoSave", 0);
		}
	}
	else if (UPlayerInfoSave* PlayerInfoSave = Cast<UPlayerInfoSave>(UGameplayStatics::CreateSaveGameObject(UPlayerInfoSave::StaticClass()))) {
		int* SavedGold = PlayerInfoSave->GetCurrentGold();
		int* SavedHealth = PlayerInfoSave->GetPlayerHealth();
		int* SavedMana = PlayerInfoSave->GetPlayerMana();
		int* SavedLiveCount = PlayerInfoSave->GetPlayerLiveCount();
		*SavedHealth = (int)this->GetCurrentHealth();
		*SavedMana = this->GetCurrentMana();
		*SavedLiveCount = LiveCount;
		if (GoldComponent) {
			*SavedGold = GoldComponent->GetCurrentGold();
		}
		UGameplayStatics::SaveGameToSlot(PlayerInfoSave, "PlayerInfoSave", 0);
	}
}

void AMainCharacter::SaveGameProgress(FName LevelName, FVector SavedLoc)
{
	if (UGameplayStatics::DoesSaveGameExist("GameProgress", 0)) {
		if (UGameProgress* GameProgress = Cast<UGameProgress>(UGameplayStatics::LoadGameFromSlot("GameProgress", 0))) {
			FVector& PlayerLocation = GameProgress->GetPlayerLocation();
			FName& CurrentLevel = GameProgress->GetLevelName();
			PlayerLocation = SavedLoc;
			CurrentLevel = LevelName;
			UGameplayStatics::SaveGameToSlot(GameProgress, "GameProgress", 0);
		}
	}
	else if (UGameProgress* GameProgress = Cast<UGameProgress>(UGameplayStatics::CreateSaveGameObject(UGameProgress::StaticClass()))) {
		FVector& PlayerLocation = GameProgress->GetPlayerLocation();
		FName& CurrentLevel = GameProgress->GetLevelName();
		PlayerLocation = SavedLoc;
		CurrentLevel = LevelName;
		UGameplayStatics::SaveGameToSlot(GameProgress, "GameProgress", 0);
	}
}

void AMainCharacter::ClearAllSaveGame()
{
	UGameplayStatics::DeleteGameInSlot("ShopSave", 0);
	UGameplayStatics::DeleteGameInSlot("GameplaySave", 0);
	UGameplayStatics::DeleteGameInSlot("PlayerInfoSave", 0);
	UGameplayStatics::DeleteGameInSlot("GameProgress", 0);
}

void AMainCharacter::EndAirAttack()
{
	if (attackCounter == 3) {
		GetCharacterMovement()->GravityScale = 1;
		AMainCharacter::EndAttack();
		AMainCharacter::EndCombo();
	}
	else {
		AMainCharacter::EndAttack();
		GetCharacterMovement()->GravityScale = 1;
	}
}

void AMainCharacter::Landed(const FHitResult& Hit)
{
	GetCharacterMovement()->GravityScale = 1;
	if (this->GetCharacterMovement()->MaxWalkSpeed == RunSpeed) {
		GetCharacterMovement()->GroundFriction = 8;
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	}
	if (CurrentState == CharacterState::ATTACK && attackCounter == 3) {
		GetAnimInstance()->JumpToNode(FName("AirSlashEnd"), FName("Attack"));
		GetWorldTimerManager().SetTimer(AttackHandle, this, &AMainCharacter::EndAirAttack, AirSlash3->GetTotalDuration(), false);
		if (isSwordSheathed == false) {
			GetWorldTimerManager().SetTimer(SheatheSwordHandle, this, &AMainCharacter::SheatheSword, AirSlash3->GetTotalDuration() + 3, false);
		}
	}
	else {
		AMainCharacter::EndAttack();
		AMainCharacter::EndCombo();
	}
	if (isSwordSheathed == false) {
		GetWorldTimerManager().SetTimer(SheatheSwordHandle, this, &AMainCharacter::SheatheSword, 3, false);
	}
}

void AMainCharacter::OnJumped_Implementation()
{
	if (attackCounter > 0) {
		AMainCharacter::EndCombo();
	}
}

