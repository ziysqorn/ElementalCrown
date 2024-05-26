// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Characters/BaseCharacter/BaseCharacter.h"
#include "CoreMinimal.h"

/**
 * 
 */
class ABaseCharacter;
class ELEMENTALCROWN_API Elemental
{
protected:
	int Buff{0};
	//Elemental name
	FName ElementalName;
	//Owning Character
	ABaseCharacter* OwningCharacter = nullptr;
public:
	//Constructor
	Elemental();
	//Destructor
	virtual ~Elemental();
	//Print test
	virtual void TestType() {
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Element Type : %s"), *ElementalName.ToString()));
		UE_LOG(LogTemp, Log, TEXT("%s"), *FString::Printf(TEXT("Element Type : %s"), *ElementalName.ToString()));
	};
	//Buff character after switching to this element
	virtual void ElementBuff() {};
	//Debuff character after switching to other element
	virtual void SwitchElementDebuff() {};
	//Set Owning character
	void SetOwningCharacter(ABaseCharacter* character) { OwningCharacter = character; }
	FName GetName() { return ElementalName; }
};
class Fire :public Elemental {
public:
	Fire();
	void ElementBuff() override;
	void SwitchElementDebuff() override;
};
class Water :public Elemental {
public:
	Water();
	void ElementBuff() override;
	void SwitchElementDebuff() override;
};
class Earth : public Elemental {
public:
	Earth();
	void ElementBuff() override;
	void SwitchElementDebuff() override;
};
class Metal : public Elemental {
public:
	Metal();
	void ElementBuff() override;
	void SwitchElementDebuff() override;
};
class Plant : public Elemental {
public:
	Plant();
	void ElementBuff() override;
	void SwitchElementDebuff() override;
};


class ELEMENTALCROWN_API ElementalNode {
protected:
	Elemental* elemental = nullptr;
public:
	ElementalNode* next = nullptr;
	ElementalNode() : elemental(nullptr), next(nullptr) {}
	ElementalNode(Elemental* val) : elemental(val), next(nullptr) {}
	ElementalNode(ElementalNode* node) : elemental(nullptr), next(node) {}
	ElementalNode(Elemental* val, ElementalNode* node) : elemental(val), next(node) {}
	virtual ~ElementalNode() {
		if (elemental) {
			delete elemental;
			elemental = nullptr;
		}
		if (next) next = nullptr;
	}
	Elemental* GetValue() { return this->elemental; }
};

class ELEMENTALCROWN_API ElementalList {
protected:
	ElementalNode* pHead = nullptr;
	ElementalNode* pTail = nullptr;
	int size = 0;
public:
	ElementalList() : pHead(nullptr), pTail(nullptr) {}
	ElementalList(ElementalNode* head, ElementalNode* tail) : pHead(head), pTail(tail) {}
	virtual ~ElementalList() {
		ElementalNode* ptr = pHead;
		while (ptr) {
			ElementalNode* current = ptr;
			ptr = ptr->next;
			delete current;
		}
		pHead = nullptr;
		pTail = nullptr;
	}
	ElementalNode* GetHead() { return pHead; }
	ElementalNode* GetTail() { return pTail; }
	int GetSize() { return size; }
	void AddTail(ElementalNode* node);
	void ClearNodes();
	void RemoveTail();
};
