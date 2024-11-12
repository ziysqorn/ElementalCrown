#include "Enemy_FireWarrior.h"

AEnemy_FireWarrior::AEnemy_FireWarrior()
{
	//Set character's base stats
	MaxHealth = Default_Character_MaxHealth - 50;
	ATK_Damage = 8;
	CurrentHealth = MaxHealth;
}
