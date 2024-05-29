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
	ABaseCharacter* OwningCharacter = nullptr;
public:
	//Constructor
	Elemental();
	Elemental(const Elemental &other) {
		Buff = other.Buff;
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	//Destructor
	virtual ~Elemental();
	//Overload = operator
	Elemental& operator=(const Elemental& other) {
		if (this == &other) return *this;
		Buff = other.Buff;
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
		return *this;
	}
	//Print test
	virtual void TestType() {
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Element Type : %s"), *ElementalName.ToString()));
		UE_LOG(LogTemp, Log, TEXT("%s"), *FString::Printf(TEXT("Element Type : %s"), *ElementalName.ToString()));
	};
	//Buff character after switching to this element
	virtual void ElementBuff() {};
	//Debuff character after switching to other element
	virtual void SwitchElementDebuff() {};
	FName GetName() { return ElementalName; }

};
class Fire :public Elemental {
public:
	Fire();
	Fire(const Fire& other) {
		Buff = other.Buff;
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	void ElementBuff() override;
	void SwitchElementDebuff() override;
};
class Water :public Elemental {
public:
	Water();
	Water(const Water& other) {
		Buff = other.Buff;
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	void ElementBuff() override;
	void SwitchElementDebuff() override;
};
class Earth : public Elemental {
public:
	Earth();
	Earth(const Earth& other) {
		Buff = other.Buff;
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	void ElementBuff() override;
	void SwitchElementDebuff() override;
};
class Metal : public Elemental {
public:
	Metal();
	Metal(const Metal& other) {
		Buff = other.Buff;
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	void ElementBuff() override;
	void SwitchElementDebuff() override;
};
class Plant : public Elemental {
public:
	Plant();
	Plant(const Plant& other) {
		Buff = other.Buff;
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
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
	}
	//Overload = operator
	ElementalNode& operator=(const ElementalNode& other) {
		if (this == &other) return *this;

		if (other.elemental->GetName().IsEqual("Fire")) elemental = new Fire(*(Fire*)other.elemental);
		else if (other.elemental->GetName().IsEqual("Water")) elemental = new Water(*(Water*)other.elemental);
		else if (other.elemental->GetName().IsEqual("Earth")) elemental = new Earth(*(Earth*)other.elemental);
		else if (other.elemental->GetName().IsEqual("Metal")) elemental = new Metal(*(Metal*)other.elemental);
		else if (other.elemental->GetName().IsEqual("Plant")) elemental = new Plant(*(Plant*)other.elemental);

		next = other.next;
		return *this;
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
	//Overload = operator
	ElementalList& operator = (const ElementalList& other) {
		if (this == &other) return *this;
		ClearNodes();
		ElementalNode* otherPtr = other.pHead;
		while (otherPtr) {
			Elemental* temp = otherPtr->GetValue();
			if(temp->GetName().IsEqual("Fire")) AddTail(new ElementalNode(new Fire(*(Fire*)temp)));
			else if(temp->GetName().IsEqual("Water")) AddTail(new ElementalNode(new Water(*(Water*)temp)));
			else if (temp->GetName().IsEqual("Earth")) AddTail(new ElementalNode(new Earth(*(Earth*)temp)));
			else if (temp->GetName().IsEqual("Metal")) AddTail(new ElementalNode(new Metal(*(Metal*)temp)));
			else if (temp->GetName().IsEqual("Plant")) AddTail(new ElementalNode(new Plant(*(Plant*)temp)));
			otherPtr = otherPtr->next;
		}
		UE_LOG(LogTemp, Log, TEXT("Hey hey bitch"));
		return *this;
	}
	ElementalNode* GetHead() { return pHead; }
	ElementalNode* GetTail() { return pTail; }
	int GetSize() { return size; }
	void AddTail(ElementalNode* node);
	void ClearNodes();
	void RemoveTail();
};
