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
	this->Buff = 2;
}

void Fire::ElementBuff(AMainCharacter* MainCharacter)
{
	MainCharacter->SetATKDamageByBuff(this->Buff);
}

void Fire::SwitchElementDebuff(AMainCharacter* MainCharacter)
{
	MainCharacter->SetATKDamageByBuff(-this->Buff);
}

Water::Water()
{
	this->Buff = 10;
}

void Water::ElementBuff(AMainCharacter* MainCharacter)
{
	MainCharacter->SetMaxHealthByBuff(this->Buff);
}

void Water::SwitchElementDebuff(AMainCharacter* MainCharacter)
{
	MainCharacter->SetMaxHealthByBuff(-this->Buff);
}

Earth::Earth()
{
	this->Buff = 3;
}

void Earth::ElementBuff(AMainCharacter* MainCharacter)
{
	MainCharacter->SetResistByBuff(this->Buff);
}

void Earth::SwitchElementDebuff(AMainCharacter* MainCharacter)
{
	MainCharacter->SetResistByBuff(-this->Buff);
}

Metal::Metal()
{
}

void Metal::ElementBuff(AMainCharacter* MainCharacter)
{
}

void Metal::SwitchElementDebuff(AMainCharacter* MainCharacter)
{
}

Plant::Plant()
{
}

void Plant::ElementBuff(AMainCharacter* MainCharacter)
{
}

void Plant::SwitchElementDebuff(AMainCharacter* MainCharacter)
{
}
