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
	TArray<BaseSkill*> SkillList;
	int CurSkillId = 0;
public:
	void AddSkill(BaseSkill* Skill) {
		if (Skill) {
			int findIdx = SkillList.Find(Skill);
			if (findIdx != INDEX_NONE) return;
			SkillList.Add(Skill);
		}
	}

	void RemoveSkill(BaseSkill* Skill) {
		if (Skill) {
			int findIdx = SkillList.Find(Skill);
			if (findIdx != INDEX_NONE) return;
			SkillList.RemoveAt(findIdx);
			delete Skill;
		}
	}

	void ChangeSkill();

	int GetCurSkillID() const {
		return CurSkillId;
	}

	int FindSkill(BaseSkill* Skill) {
		int res = INDEX_NONE;
		res = SkillList.Find(Skill);
		return res;
	}

	BaseSkill* FindSkill(int findIdx) {
		return SkillList[findIdx];
	}

	TArray<BaseSkill*>* GetSkillList() {
		return &SkillList;
	}

	void UseSkill() {
		if (SkillList.IsValidIndex(CurSkillId) && SkillList[CurSkillId]) {
			SkillList[CurSkillId]->SetOwningCharacter(Cast<ABaseCharacter>(this->GetOwner()));
			SkillList[CurSkillId]->PerformSkill();
		}
	}

public:
	virtual void BeginPlay() override;

};