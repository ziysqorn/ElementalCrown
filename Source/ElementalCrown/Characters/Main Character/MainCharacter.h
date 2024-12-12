// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter/BaseCharacter.h"
#include "../../Effects/Smoke/Smoke.h"
#include "../../SkillsIncludes.h"
#include "../../Consumable/ConsumableComponent.h"
#include "../../Gold/GoldComponent.h"
#include "MainCharacter.generated.h"

/**
 * 
 */

using namespace Constants;
UCLASS() 
class ELEMENTALCROWN_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()
protected:
	//Spring Arm and Camera Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spring Arm")
	USpringArmComponent* SpringArmComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paper TileMap Component")
	UPaperTileMapComponent* PaperTileMapComp = nullptr;

	//Input Action 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Move = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Dodge = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Jump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_UseSkill = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Attack = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Shoot = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_ChangeSkill = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Interact = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_UseHealPot = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_UseManaPot = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_UseBleedCurePot = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_UseBurnCurePot = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_UseDrowsyCurePot = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_UseStunCurePot = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_UseVulnerableCurePot = nullptr;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Run smoke")
	TSubclassOf<ASmoke> RunSmokeSubclass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Consumable component")
	UConsumableComponent* ConsumableComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Gold component")
	UGoldComponent* GoldComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Consumable DataTable")
	UDataTable* DT_Consumable = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Skill DataTable")
	UDataTable* DT_Skill = nullptr;

	//Timer Handle
	FTimerHandle ComboHandle;
	FTimerHandle SheatheSwordHandle;

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
	UConsumableComponent* GetConsumableComp() {
		return ConsumableComponent;
	}
	UGoldComponent* GetGoldComp() {
		return GoldComponent;
	}


	//Actions
	virtual void Move(const FInputActionValue& value);
	virtual void StopMoving();
	void Dodge();
	void CustomJump();
	virtual void Attack();
	virtual void Shoot();
	void UseSkill();
	void ChangeSkill();
	void Interact();
	void LoadGameplayFromSave();
	void LoadInfoFromSave();
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
	void Dead() override;
	//Events
	//Event begin play
	void BeginPlay() override;
	//Event tick
	void Tick(float DeltaSeconds) override;
	//Event landed
	void Landed(const FHitResult& Hit) override;
	//Event on jumped
	void OnJumped_Implementation() override;
};
