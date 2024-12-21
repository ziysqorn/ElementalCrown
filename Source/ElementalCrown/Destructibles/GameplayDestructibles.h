// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "GameplayDestructibles.generated.h"

UCLASS()
class ELEMENTALCROWN_API AGameplayDestructibles : public AActor
{
	GENERATED_BODY()
protected:
	//This actor's stats
	int Health{10};
	
	int maxBountyPrice = 8;
public:	
	// Sets default values for this actor's properties
	AGameplayDestructibles();
	AGameplayDestructibles(const TCHAR* SpriteRef, const TCHAR* DamagedSpriteRef, const TCHAR* CurveRef);
	//Getter
	int GetHealth() {
		return Health;
	}
	//Setter
	void UpdateHealth(const int &Difference) {
		Health += Difference;
	}
	//
	UFUNCTION()
	void FlashDamage(const float &Value);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Sprite Component")
	UPaperSpriteComponent* ObjectSprite = nullptr;

	UPaperSprite* DamagedSprite = nullptr;

	UPaperSprite* IniSprite = nullptr;

	UCurveFloat* FlashCurveFloat = nullptr;

	FTimeline FlashTimeline;

	FTimerHandle DeadHandle;

public:
	//Events
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void DestructibleDestroyed();
};
