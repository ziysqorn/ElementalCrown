// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "../../Controller/MainController.h"

AMainCharacter::AMainCharacter()
{
	//Components setup
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
	ConsumableComponent = CreateDefaultSubobject<UConsumableComponent>(TEXT("ConsumableComponent"));
	//Character movement
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;
	GetCharacterMovement()->MaxFlySpeed = RunSpeed;
	GetCharacterMovement()->AirControl = 0.75;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	SkillComponent->AddSkill(new GaleBurst());
	SkillComponent->AddSkill(new StoneBarrageSkill());
	SkillComponent->AddSkill(new PoseidonAura());
	SkillComponent->AddSkill(new RazorWaveSkill());


}

AMainCharacter::~AMainCharacter()
{
}

void AMainCharacter::BeginPlay()
{

	ABaseCharacter::BeginPlay();

	//Setup mapping context
	SetupMappingContext();

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
}

void AMainCharacter::Tick(float DeltaSeconds)
{
	ABaseCharacter::Tick(DeltaSeconds);
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
			EIComponent->BindAction(IA_UseHealPot, ETriggerEvent::Triggered, ConsumableComponent, &UConsumableComponent::UseHealPot);
			EIComponent->BindAction(IA_UseManaPot, ETriggerEvent::Triggered, ConsumableComponent, &UConsumableComponent::UseManaPot);
			EIComponent->BindAction(IA_OpenShop, ETriggerEvent::Triggered, MainController, &AMainController::OpenShop);
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
			if (CurrentState == CharacterState::DODGE) {
				CurrentState = CharacterState::NONE;
				GetCapsuleComponent()->SetCollisionObjectType(ECC_Pawn);
				GetCharacterMovement()->GravityScale = 1.0f;
			}
			}), 0.35f, false);
		this->GetWorldTimerManager().SetTimer(DodgeEnableHandle, FTimerDelegate::CreateLambda([this]() {
			if (!canDodge) canDodge = true;
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
		}
		else
		AMainCharacter::Jump();
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

void AMainCharacter::UseSkill()
{
	if (CurrentState == CharacterState :: NONE) SkillComponent->UseSkill();
}


void AMainCharacter::ChangeSkill()
{
	SkillComponent->ChangeSkill();
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

