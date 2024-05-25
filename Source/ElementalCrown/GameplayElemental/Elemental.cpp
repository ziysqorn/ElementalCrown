// Fill out your copyright notice in the Description page of Project Settings.


#include "Elemental.h"

Elemental::Elemental()
{
}

Elemental::~Elemental()
{
}

Fire::Fire()
{
	ElementalName = "Fire";
	this->Buff = 2;
}

void Fire::ElementBuff()
{
	if(OwningCharacter) OwningCharacter->SetATKDamageByBuff(this->Buff);
}

void Fire::SwitchElementDebuff()
{
	if (OwningCharacter) OwningCharacter->SetATKDamageByBuff(-this->Buff);
}

Water::Water()
{
	ElementalName = "Water";
	this->Buff = 10;
}

void Water::ElementBuff()
{
	if (OwningCharacter) OwningCharacter->SetMaxHealthByBuff(this->Buff);
}

void Water::SwitchElementDebuff()
{
	if (OwningCharacter) OwningCharacter->SetMaxHealthByBuff(-this->Buff);
}

Earth::Earth()
{
	ElementalName = "Earth";
	this->Buff = 3;
}

void Earth::ElementBuff()
{
	if (OwningCharacter) OwningCharacter->SetResistByBuff(this->Buff);
}

void Earth::SwitchElementDebuff()
{
	if (OwningCharacter) OwningCharacter->SetResistByBuff(-this->Buff);
}

Metal::Metal()
{
	ElementalName = "Metal";
}

void Metal::ElementBuff()
{
}

void Metal::SwitchElementDebuff()
{
}

Plant::Plant()
{
	ElementalName = "Plant";
}

void Plant::ElementBuff()
{
}

void Plant::SwitchElementDebuff()
{
}

void ElementalList::AddTail(ElementalNode* node)
{
	if (pHead) {
		pTail->next = node;
		pTail = pTail->next;
	}
	else {
		pHead = node;
		pTail = node;
	}
	++size;
}

void ElementalList::ClearNodes()
{
	ElementalNode* ptr = pHead;
	while (ptr) {
		ElementalNode* current = ptr;
		ptr = ptr->next;
		delete current;
	}
	pHead = nullptr;
	pTail = nullptr;
	size = 0;
}

void ElementalList::RemoveTail()
{
	if (pHead) {
		ElementalNode* prev = nullptr;
		ElementalNode* ptr = pHead;
		while (0 == 0) {
			if (ptr == pTail) {
				pTail = prev;
				delete ptr;
				ptr = nullptr;
				return;
			}
			prev = ptr;
			ptr = ptr->next;
			--size;
		}
	}
}
