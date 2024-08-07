// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "../../Controller/MainController.h"

AMainCharacter::AMainCharacter()
{
	//Allocate pointers
	//Components setup
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
	//Character movement
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;
	GetCharacterMovement()->MaxFlySpeed = RunSpeed;
	GetCharacterMovement()->AirControl = 0.75;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	//Add Delegates
	this->OnActorBeginOverlap.AddDynamic(this, &AMainCharacter::BeginOverlap);

	CharElementalList = MakeShared<CustomLinkedList<Elemental>>();
	FireSkillList = MakeShared<CustomLinkedList<BaseSkill>>();
	WaterSkillList = MakeShared<CustomLinkedList<BaseSkill>>();
	CharElementalList->AddTail(new CustomNode<Elemental>(new Fire(this)));
	CharElementalList->AddTail(new CustomNode<Elemental>(new Water(this)));
	FireSkillList->AddTail(new CustomNode<BaseSkill>(new VolcanicFire()));
	FireSkillList->AddTail(new CustomNode<BaseSkill>(new FireEnergy()));
	WaterSkillList->AddTail(new CustomNode<BaseSkill>(new AquaSphere()));
	CharSkillList = FireSkillList;
	CharacterElement = CharElementalList->GetHead();
	CharacterSkill = CharSkillList->GetHead();
}

AMainCharacter::~AMainCharacter()
{
}

void AMainCharacter::BeginPlay()
{

	ABaseCharacter::BeginPlay();

	//Setup mapping context
	SetupMappingContext();

	if (AMainController* MainController = Cast<AMainController>(this->GetController())) {
		if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
			MainHUD->SwitchedSlotHighlight(CharacterElement);
			MainHUD->SwitchedSlotHighlight(CharacterSkill);
		}
	}
}

void AMainCharacter::Tick(float DeltaSeconds)
{
	ABaseCharacter::Tick(DeltaSeconds);
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EIComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EIComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		EIComponent->BindAction(IA_Move, ETriggerEvent::Completed, this, &AMainCharacter::StopMoving);
		EIComponent->BindAction(IA_Run, ETriggerEvent::Triggered, this, &AMainCharacter::Run);
		EIComponent->BindAction(IA_Run, ETriggerEvent::Completed, this, &AMainCharacter::StopRunning);
		EIComponent->BindAction(IA_Crouch, ETriggerEvent::Triggered, this, &AMainCharacter::CustomCrouch);
		EIComponent->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &AMainCharacter::StopCustomCrouch);
		EIComponent->BindAction(IA_UseSkill, ETriggerEvent::Triggered, this, &AMainCharacter::UseSkill);
		EIComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AMainCharacter::CustomJump);
		EIComponent->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &AMainCharacter::Attack);
		EIComponent->BindAction(IA_Shoot, ETriggerEvent::Triggered, this, &AMainCharacter::Shoot);
		EIComponent->BindAction(IA_ChangeElement, ETriggerEvent::Triggered, this, &AMainCharacter::ChangeElement);
		EIComponent->BindAction(IA_ChangeSkill, ETriggerEvent::Triggered, this, &AMainCharacter::ChangeSkill);
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
			//Spawn run smoke
			if ((abs(abs(GetVelocity().X)-(MoveSpeed + 125.00f)) <= 15) && GetVelocity().Z==0) {
				FVector SpawnLocation = this->GetActorLocation();
				FRotator SpawnRotation = (DirectionValue > 0) ? FRotator(0, 180, 0) : FRotator(0, 0, 0);
				FActorSpawnParameters SpawnParams;
				SpawnLocation.Y += 1.1;
				float CapsualeHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
				SpawnLocation.Z = SpawnLocation.Z - (CapsualeHalfHeight / 2);
				SpawnLocation.X+= (DirectionValue > 0) ? -10 : 10;
				SpawnParams.Owner = this;
				GetWorld()->SpawnActor<ARunSmoke>(ARunSmoke::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
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

void AMainCharacter::Run()
{
	if (CurrentState != CharacterState::SLIDE && this->GetVelocity().Z == 0) {
		GetCharacterMovement()->GroundFriction = 0;
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}

void AMainCharacter::StopMoving()
{
	if (this->GetCharacterMovement()->GravityScale < 1) {
		this->GetCharacterMovement()->GravityScale = 1;
	}
}

void AMainCharacter::StopRunning()
{
	if (CurrentState!=CharacterState::SLIDE && this->GetVelocity().Z == 0) {
		GetCharacterMovement()->GroundFriction = 8;
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	}
}

void AMainCharacter::CustomCrouch()
{
	if (this->GetVelocity().Z == 0 && CurrentState != CharacterState::ATTACK && CurrentState!=CharacterState::SLIDE && CurrentState!=CharacterState::DODGE) {
		if (abs(this->GetVelocity().X) == RunSpeed) {
			AMainCharacter::Slide();
		}
		else {
			AMainCharacter::Crouch();
		}
	}
}

void AMainCharacter::StopCustomCrouch()
{
	if (GetCharacterMovement()->IsCrouching()) {
		if (CurrentState != CharacterState::SLIDE) {
			AMainCharacter::UnCrouch();
		}
	}
}

void AMainCharacter::Slide()
{
	GetCharacterMovement()->BrakingDecelerationWalking = 400;
	GetCharacterMovement()->MaxWalkSpeedCrouched = RunSpeed;
	CurrentState = CharacterState::SLIDE;
	AMainCharacter::Crouch();
	if (Sliding) {
		GetWorldTimerManager().SetTimer(SlideHandle, this, &AMainCharacter::StopSlide, Sliding->GetTotalDuration(), false);
	}
}

void AMainCharacter::StopSlide()
{
	GetCharacterMovement()->BrakingDecelerationWalking = 2048;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;
	AMainCharacter::UnCrouch();
	if(CurrentState == CharacterState::SLIDE)
		CurrentState = CharacterState::NONE;
	AMainCharacter::StopRunning();
}

void AMainCharacter::CustomJump()
{
	if (CurrentState != CharacterState::ATTACK) {
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
	if (CharacterSkill->GetValue()) {
		CharacterSkill->GetValue()->SetOwningCharacter(this);
		CharacterSkill->GetValue()->PerformSkill();
	}
}

void AMainCharacter::ChangeElement()
{
	if (CharacterElement == CharElementalList->GetTail()) CharacterElement = CharElementalList->GetHead();
	else {
		if (CharacterElement->next != nullptr) CharacterElement = CharacterElement->next;
	}
	if (CharacterElement->GetValue()->GetName().IsEqual("Fire")) CharSkillList = FireSkillList;
	else if (CharacterElement->GetValue()->GetName().IsEqual("Water")) CharSkillList = WaterSkillList;
	else if (CharacterElement->GetValue()->GetName().IsEqual("Earth")) CharSkillList = EarthSkillList;
	else if (CharacterElement->GetValue()->GetName().IsEqual("Metal")) CharSkillList = MetalSkillList;
	else if (CharacterElement->GetValue()->GetName().IsEqual("Plant")) CharSkillList = PlantSkillList;
	CharacterSkill = CharSkillList->GetHead();
	if (AMainController* MainController = Cast<AMainController>(this->GetController())) {
		if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) 
		{
			MainHUD->SwitchedSlotHighlight(CharacterElement);
			MainHUD->RefreshSkillSlots(CharSkillList);
		}
	}
}

void AMainCharacter::ChangeSkill()
{
	if (CharacterSkill == CharSkillList->GetTail()) CharacterSkill = CharSkillList->GetHead();
	else {
		if (CharacterSkill->next != nullptr) CharacterSkill = CharacterSkill->next;
	}
	if (AMainController* MainController = Cast<AMainController>(this->GetController())) {
		if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) MainHUD->SwitchedSlotHighlight(CharacterSkill);
	}
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

void AMainCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
}

void AMainCharacter::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (this->GetVelocity().Z < 0) {
		if (this->CurrentState == CharacterState::ATTACK) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Slash down"));
	}
}

