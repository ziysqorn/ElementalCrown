// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenMessage.h"

void UScreenMessage::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UScreenMessage::NativeConstruct()
{
	Super::NativeConstruct();

	FWidgetAnimationDynamicEvent Del;
	Del.BindUFunction(this, FName("AnimEndAction"));
	BindToAnimationFinished(Fadein, Del);
}

void UScreenMessage::AnimEndAction()
{

}

void UScreenMessage::PlayFadein()
{
	if (Fadein) {
		PlayAnimationForward(Fadein);
	}
}
