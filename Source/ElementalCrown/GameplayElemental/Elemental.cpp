// Fill out your copyright notice in the Description page of Project Settings.


#include "Elemental.h"

Elemental::Elemental()
{
}

Elemental::Elemental(ABaseCharacter* character)
{
	OwningCharacter = character;
}

Elemental::~Elemental()
{
}

Fire::Fire()
{
	ElementalName = "Fire";
	this->Buff = 2;
}

Fire::Fire(ABaseCharacter* character) : Elemental(character)
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

Water::Water(ABaseCharacter* character) : Elemental(character)
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

Earth::Earth(ABaseCharacter* character) : Elemental(character)
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

Metal::Metal(ABaseCharacter* character) : Elemental(character)
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

Plant::Plant(ABaseCharacter* character) : Elemental(character)
{
	ElementalName = "Plant";
}

void Plant::ElementBuff()
{
}

void Plant::SwitchElementDebuff()
{
}
