// Fill out your copyright notice in the Description page of Project Settings.


#include "Elemental.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "../Controller/MainController.h"
#include "../Effects/Skills/SkillEffect.h"

UElemental::UElemental()
{
}

UElemental::UElemental(const TCHAR* Ref)
{
	ConstructorHelpers::FClassFinder<UStatusEffectProgressUI> ProgressUIClass(Ref);
	if (ProgressUIClass.Succeeded()) StatusProgressUISubClass = ProgressUIClass.Class;
}

UFire::UFire() : UElemental(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/StatusEffectProgressUI/BP_FireProgressUI.BP_FireProgressUI_C'"))
{
	ElementalName = "Fire";
}

void UFire::ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup)
{
	if (AffectedCharacter && AffectedCharacter->GetCharacterState() != CharacterState::DEATH) {
		auto CurEffectList = AffectedCharacter->GetStatusList();
		for (int i = 0; i < CurEffectList->Num(); ++i) {
			UBaseStatusEffect* value = (*CurEffectList)[i];
			if (IsValid(value) && value->GetStatusName().IsEqual("Burn")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(inBuildup);
				return;
			}
		}
		UBaseStatusEffect* newStatus = NewObject<UBurnStatus>(this, UBurnStatus::StaticClass(), TEXT("BurnStatus"));
		CurEffectList->Add(newStatus);
		if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter())) 
			newStatus->SetOwningCharacter(Cast<ABaseCharacter>(SkillEffect->GetOwner()));
		else if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter()))
			newStatus->SetOwningCharacter(Cast<ABaseCharacter>(BaseCharacter));
		newStatus->SetAffectedCharacter(AffectedCharacter);
		newStatus->BuildingUp(inBuildup);
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(AffectedCharacter)) {
			if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
				if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
					UStatusEffectProgressUI* Progress = CreateWidget<UStatusEffectProgressUI>(MainHUD, StatusProgressUISubClass);
					if (Progress) {
						Progress->GetProgressBar()->PercentDelegate.BindUFunction(newStatus, FName("GetBuildupPercentage"));
						MainHUD->AddStatsEffectToVerBox(Progress);
					}
				}
			}
		}
	}
}

UWater::UWater() : UElemental(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/StatusEffectProgressUI/BP_VulnerableProgressUI.BP_VulnerableProgressUI_C'"))
{
	ElementalName = "Water";
}

void UWater::ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup)
{
	if (AffectedCharacter && AffectedCharacter->GetCharacterState() != CharacterState::DEATH) {
		auto CurEffectList = AffectedCharacter->GetStatusList();
		for (int i = 0; i < CurEffectList->Num(); ++i) {
			UBaseStatusEffect* value = (*CurEffectList)[i];
			if (IsValid(value) && value->GetStatusName().IsEqual("Vulnerable")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(inBuildup);
				return;
			}
		}
		UBaseStatusEffect* newStatus = NewObject<UVulnerableStatus>(this, UVulnerableStatus::StaticClass(), TEXT("VulnerableStatus"));
		CurEffectList->Add(newStatus);
		if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter()))
			newStatus->SetOwningCharacter(Cast<ABaseCharacter>(SkillEffect->GetOwner()));
		else if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter()))
			newStatus->SetOwningCharacter(Cast<ABaseCharacter>(BaseCharacter));
		newStatus->SetAffectedCharacter(AffectedCharacter);
		newStatus->BuildingUp(inBuildup);
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(AffectedCharacter)) {
			if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
				if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
					UStatusEffectProgressUI* Progress = CreateWidget<UStatusEffectProgressUI>(MainHUD, StatusProgressUISubClass);
					if (Progress) {
						Progress->GetProgressBar()->PercentDelegate.BindUFunction(newStatus, FName("GetBuildupPercentage"));
						MainHUD->AddStatsEffectToVerBox(Progress);
					}
				}
			}
		}
	}
}

UEarth::UEarth() : UElemental(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/StatusEffectProgressUI/BP_StunProgressUI.BP_StunProgressUI_C'"))
{
	ElementalName = "Earth";
}

void UEarth::ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup)
{
	if (AffectedCharacter && AffectedCharacter->GetCharacterState() != CharacterState::DEATH) {
		auto CurEffectList = AffectedCharacter->GetStatusList();
		for (int i = 0; i < CurEffectList->Num(); ++i) {
			UBaseStatusEffect* value = (*CurEffectList)[i];
			if (IsValid(value) && value->GetStatusName().IsEqual("Stun")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(inBuildup);
				return;
			}
		}
		UBaseStatusEffect* newStatus = NewObject<UStunStatus>(this, UStunStatus::StaticClass(), TEXT("StunStatus"));
		CurEffectList->Add(newStatus);
		if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter()))
			newStatus->SetOwningCharacter(Cast<ABaseCharacter>(SkillEffect->GetOwner()));
		else if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter()))
			newStatus->SetOwningCharacter(Cast<ABaseCharacter>(BaseCharacter));
		newStatus->SetAffectedCharacter(AffectedCharacter);
		newStatus->BuildingUp(inBuildup);
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(AffectedCharacter)) {
			if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
				if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
					UStatusEffectProgressUI* Progress = CreateWidget<UStatusEffectProgressUI>(MainHUD, StatusProgressUISubClass);
					if (Progress) {
						Progress->GetProgressBar()->PercentDelegate.BindUFunction(newStatus, FName("GetBuildupPercentage"));
						MainHUD->AddStatsEffectToVerBox(Progress);
					}
				}
			}
		}
	}
}


UMetal::UMetal() : UElemental(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/StatusEffectProgressUI/BP_BleedProgressUI.BP_BleedProgressUI_C'"))
{
	ElementalName = "Metal";
}

void UMetal::ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup)
{
	if (AffectedCharacter && AffectedCharacter->GetCharacterState() != CharacterState::DEATH) {
		auto CurEffectList = AffectedCharacter->GetStatusList();
		for (int i = 0; i < CurEffectList->Num(); ++i) {
			UBaseStatusEffect* value = (*CurEffectList)[i];
			if (IsValid(value) && value->GetStatusName().IsEqual("Bleed")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(inBuildup);
				return;
			}
		}
		UBaseStatusEffect* newStatus = NewObject<UBleedStatus>(this, UBleedStatus::StaticClass(), TEXT("BleedStatus"));
		CurEffectList->Add(newStatus);
		if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter()))
			newStatus->SetOwningCharacter(Cast<ABaseCharacter>(SkillEffect->GetOwner()));
		else if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter()))
			newStatus->SetOwningCharacter(Cast<ABaseCharacter>(BaseCharacter));
		newStatus->SetAffectedCharacter(AffectedCharacter);
		newStatus->BuildingUp(inBuildup);
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(AffectedCharacter)) {
			if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
				if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
					UStatusEffectProgressUI* Progress = CreateWidget<UStatusEffectProgressUI>(MainHUD, StatusProgressUISubClass);
					if (Progress) {
						Progress->GetProgressBar()->PercentDelegate.BindUFunction(newStatus, FName("GetBuildupPercentage"));
						MainHUD->AddStatsEffectToVerBox(Progress);
					}
				}
			}
		}
	}
}

UPlant::UPlant() : UElemental(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/StatusEffectProgressUI/BP_DrowsyProgressUI.BP_DrowsyProgressUI_C'"))
{
	ElementalName = "Plant";
}

void UPlant::ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup)
{
	if (AffectedCharacter && AffectedCharacter->GetCharacterState() != CharacterState::DEATH) {
		auto CurEffectList = AffectedCharacter->GetStatusList();
		for (int i = 0; i < CurEffectList->Num(); ++i) {
			UBaseStatusEffect* value = (*CurEffectList)[i];
			if (IsValid(value) && value->GetStatusName().IsEqual("Drowsy")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(inBuildup);
				return;
			}
		}
		UBaseStatusEffect* newStatus = NewObject<UDrowsyStatus>(this, UDrowsyStatus::StaticClass(), TEXT("DrowsyStatus"));
		CurEffectList->Add(newStatus);
		if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter()))
			newStatus->SetOwningCharacter(Cast<ABaseCharacter>(SkillEffect->GetOwner()));
		else if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter()))
			newStatus->SetOwningCharacter(Cast<ABaseCharacter>(BaseCharacter));
		newStatus->SetAffectedCharacter(AffectedCharacter);
		newStatus->BuildingUp(inBuildup);
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(AffectedCharacter)) {
			if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
				if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
					UStatusEffectProgressUI* Progress = CreateWidget<UStatusEffectProgressUI>(MainHUD, StatusProgressUISubClass);
					if (Progress) {
						Progress->GetProgressBar()->PercentDelegate.BindUFunction(newStatus, FName("GetBuildupPercentage"));
						MainHUD->AddStatsEffectToVerBox(Progress);
					}
				}
			}
		}
	}
}
