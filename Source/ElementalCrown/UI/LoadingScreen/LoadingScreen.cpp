// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingScreen.h"
#include "Animation/UMGSequencePlayer.h"

void ULoadingScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void ULoadingScreen::PlayReverseImmediate()
{
	PlayAnimationReverse(FadeinBackground);
	GetWorld()->GetTimerManager().SetTimer(FadeAwayEndHandle, FTimerDelegate::CreateUObject(this, &ULoadingScreen::LoadEndAction), abs(FadeinBackground->GetStartTime() - FadeinBackground->GetEndTime()), false);
}

void ULoadingScreen::LoadEndAction()
{
	LoadingScreenEndDel.ExecuteIfBound();
	this->RemoveFromParent();
	//this->ConditionalBeginDestroy();
}

void ULoadingScreen::PlayFadeinAnim()
{
	if (FadeinBackground) {
		PlayAnimationForward(FadeinBackground);
	}
}

void ULoadingScreen::PlayFadeinAnimReverse()
{
	if (FadeinBackground) {
		GetWorld()->GetTimerManager().SetTimer(LoadTimeHandle, FTimerDelegate::CreateUObject(this, &ULoadingScreen::PlayReverseImmediate), 6.0f, false);
	}
}
