// Fill out your copyright notice in the Description page of Project Settings.

#include "C_MainMenuPC.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void AC_MainMenuPC::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Outer;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("MainMenuCam"), Outer);

	if (Outer.IsValidIndex(0))
	{
		SetViewTarget(Outer[0]);
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("MainMenuCam is Not Exist. Fatal Error!!!"));
	}

	GI = Cast<UC_ReverseGI>(GetGameInstance());
	if (!(GI->IsValidLowLevel()))
	{
		UE_LOG(LogClass, Warning, TEXT("GI Cast Error. In MainMenuPC"));
	}

	GetWorldTimerManager().SetTimer(TimeReverse, this, &AC_MainMenuPC::DoReverse, 10.f, false);
}

void AC_MainMenuPC::DoReverse()
{
	GetWorldTimerManager().ClearTimer(TimeReverse);
	if (GI)
	{
		GI->ReverseActivate();
	}
	GetWorldTimerManager().SetTimer(TimeReverse, this, &AC_MainMenuPC::DoUnReverse, 12.f, false);
}

void AC_MainMenuPC::DoUnReverse()
{
	GetWorldTimerManager().ClearTimer(TimeReverse);
	if (GI) 
	{
		GI->ReverseDeActivate();
	}
	GetWorldTimerManager().SetTimer(TimeReverse, this, &AC_MainMenuPC::DoReverse, 10.f, false);
}