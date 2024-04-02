// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrel.h"

ABarrel::ABarrel() : AGameplayDestructibles(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Destructibles/Barrel/barrel_Sprite.barrel_Sprite'"), TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Destructibles/Barrel/barrel_damaged_Sprite.barrel_damaged_Sprite'"), TEXT("/Script/Engine.CurveFloat'/Game/Curve/DamagedFlash/CF_FlashDamage.CF_FlashDamage'"))
{
}
