// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseSkill.h"
#include "SkillComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ELEMENTALCROWN_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	TArray<UBaseSkill*> SkillList;

	UPROPERTY()
	TArray<UBaseSkill*> OwnedSkillList;

	UPROPERTY(EditDefaultsOnly, Category = "Important")
	UDataTable* DT_Skill = nullptr;

	int CurSkillId = 0;
public:
	void AddSkill(UBaseSkill* Skill) {
		if (Skill) {
			int findIdx = SkillList.Find(Skill);
			if (findIdx != INDEX_NONE) return;
			SkillList.Add(Skill);
		}
	}

	void AddOwnedSkill(UBaseSkill* Skill) {
		if (Skill) {
			int findIdx = OwnedSkillList.Find(Skill);
			if (findIdx != INDEX_NONE) return;
			OwnedSkillList.Add(Skill);
		}
	}

	void RemoveSkill(UBaseSkill* Skill) {
		if (Skill) {
			int findIdx = SkillList.Find(Skill);
			if (findIdx != INDEX_NONE) return;
			SkillList.RemoveAt(findIdx);
		}
	}

	void RemoveOwnedSkill(UBaseSkill* Skill) {
		if (Skill) {
			int findIdx = OwnedSkillList.Find(Skill);
			if (findIdx != INDEX_NONE) return;
			OwnedSkillList.RemoveAt(findIdx);
		}
	}

	void ChangeSkill();

	int GetCurSkillID() const {
		return CurSkillId;
	}

	int FindSkill(UBaseSkill* Skill) {
		int res = INDEX_NONE;
		res = SkillList.Find(Skill);
		return res;
	}

	int FindOwnedSkill(UBaseSkill* Skill) {
		int res = INDEX_NONE;
		res = OwnedSkillList.Find(Skill);
		return res;
	}


	UBaseSkill* FindSkill(FName inName) {
		UBaseSkill** FoundSkillPtr = SkillList.FindByPredicate([inName](UBaseSkill* Skill) {
			return Skill->GetSkillName().IsEqual(inName);
			});
		return FoundSkillPtr ? *FoundSkillPtr : nullptr;
	}

	UBaseSkill* FindOwnedSkill(FName inName) {
		UBaseSkill** FoundSkillPtr = OwnedSkillList.FindByPredicate([inName](UBaseSkill* Skill) {
			return Skill->GetSkillName().IsEqual(inName);
			});
		return FoundSkillPtr ? *FoundSkillPtr : nullptr;
	}

	UBaseSkill* FindSkill(int findIdx) {
		if (!SkillList.IsValidIndex(findIdx)) return nullptr;
		return SkillList[findIdx];
	}

	UBaseSkill* FindOwnedSkill(int findIdx) {
		if (!OwnedSkillList.IsValidIndex(findIdx)) return nullptr;
		return OwnedSkillList[findIdx];
	}

	TArray<UBaseSkill*>* GetSkillList() {
		return &SkillList;
	}

	TArray<UBaseSkill*>* GetOwnedSkillList() {
		return &OwnedSkillList;
	}

	void UseSkill() {
		if (SkillList.IsValidIndex(CurSkillId) && SkillList[CurSkillId]) SkillList[CurSkillId]->PerformSkill();
	}

	void LoadSkill();

public:
	virtual void BeginPlay() override;

};