// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "../BaseCharacter/BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "../../Effects/Smoke/RunSmoke/RunSmoke.h"
#include "../../Skill/ExplodeSkill/VolcanicFire/VolcanicFire.h"
#include "../../Skill/EjectSkill/FireEnergy/FireEnergy.h"
#include "../../Skill/EjectSkill/AquaSphere/AquaSphere.h"
#include "../../DataStructs/CustomLinkedList.h"
#include "../../Interface/BaseCharacterInterface.h"
#include "TimerManager.h"
#include "../../Constants/Constants.h"
#include "../../Enums/Enums.h"
#include "MainCharacter.generated.h"

/**
 * 
 */

using namespace Constants;
UCLASS() 
class ELEMENTALCROWN_API AMainCharacter : public ABaseCharacter, public IBaseCharacterInterface
{
	GENERATED_BODY()
protected:
	CustomNode<Elemental>* CharacterElement = nullptr;
	CustomNode<BaseSkill>* CharacterSkill = nullptr;
	std::shared_ptr<CustomLinkedList<Elemental>> CharElementalList;
	std::shared_ptr<CustomLinkedList<BaseSkill>> CharSkillList;
	std::shared_ptr<CustomLinkedList<BaseSkill>> FireSkillList;
	std::shared_ptr<CustomLinkedList<BaseSkill>> WaterSkillList;
	std::shared_ptr<CustomLinkedList<BaseSkill>> EarthSkillList;
	std::shared_ptr<CustomLinkedList<BaseSkill>> MetalSkillList;
	std::shared_ptr<CustomLinkedList<BaseSkill>> PlantSkillList;
protected:
	//Spring Arm and Camera Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spring Arm")
	USpringArmComponent* SpringArmComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComp = nullptr;

	//Input Action 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Move = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Run = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Jump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Crouch = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_UseSkill = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Attack = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Shoot = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_ChangeElement = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_ChangeSkill = nullptr;

	//Input mapping context
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputMapping")
	UInputMappingContext* MainMappingContext = nullptr;

	//Animation Sequences
	//Sword default combo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Slash Default Combo")
	UPaperZDAnimSequence* Slash1 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Slash Default Combo")
	UPaperZDAnimSequence* Slash2 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Slash Default Combo")
	UPaperZDAnimSequence* Slash3 = nullptr;

	//Sword air combo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Air Slash Combo")
	UPaperZDAnimSequence* AirSlash1 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Air Slash Combo")
	UPaperZDAnimSequence* AirSlash2 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Air Slash Combo")
	UPaperZDAnimSequence* AirSlash3 = nullptr;
	//Bow-combat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Bow-combat")
	UPaperZDAnimSequence* BowShoot = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Bow-combat")
	UPaperZDAnimSequence* JumpShoot = nullptr;

	//Character movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Slide")
	UPaperZDAnimSequence* Sliding = nullptr;

	//Timer Handle
	FTimerHandle ComboHandle;
	FTimerHandle SheatheSwordHandle;
	FTimerHandle SlideHandle;

	//Sheathe the sword
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Is the Sword Sheathed ?")
	bool isSwordSheathed{ true };

	//Attack counter
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack Counter")
	int attackCounter{0};

	//Check character is sliding on the wall
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character hit a wall ?")
	bool WallSliding{ false };

public:
	AMainCharacter();
	~AMainCharacter();
	//Inputs settup
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetupMappingContext();
	//Getter
	UFUNCTION(BlueprintCallable)
	float const GetMoveSpeed() {
		return MoveSpeed;
	}
	UFUNCTION(BlueprintCallable)
	float const GetCrouchSpeed() {
		return CrouchSpeed;
	}
	UFUNCTION(BlueprintCallable)
	float const GetRunSpeed() {
		return RunSpeed;
	}
	UFUNCTION(BlueprintCallable)
	int GetATKDamage() {
		return ATK_Damage;
	}
	
	std::shared_ptr<CustomLinkedList<Elemental>> GetElementalList() { return CharElementalList; }
	std::shared_ptr<CustomLinkedList<BaseSkill>> GetSkillList() { return CharSkillList; }

	//Actions
	virtual void Move(const FInputActionValue& value);
	virtual void StopMoving();
	void Run();
	void StopRunning();
	void CustomCrouch();
	void StopCustomCrouch();
	void Slide();
	void StopSlide();
	void CustomJump();
	virtual void Attack();
	virtual void Shoot();
	void UseSkill();
	void ChangeElement();
	void ChangeSkill();
	void SheatheSword() {
		isSwordSheathed = true;
	}
	virtual void EndAttack() {
		if(CurrentState == CharacterState::ATTACK || CurrentState == CharacterState::SHOOT)
		CurrentState = CharacterState::NONE;
	}
	void EndAirAttack();
	virtual void EndCombo() {
		attackCounter = 0;
	}
	//Events
	//Event begin play
	void BeginPlay() override;
	//Event tick
	void Tick(float DeltaSeconds) override;
	//Event landed
	void Landed(const FHitResult& Hit) override;
	//Event on jumped
	void OnJumped_Implementation() override;
	//Event begin hit
	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	//Event begin overlap
	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
