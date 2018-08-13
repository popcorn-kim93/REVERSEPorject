// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_ReverseGI.h"
#include "C_MainMenuPC.generated.h"

/**
 * 
 */
UCLASS()
class REVERSEPROJ_API AC_MainMenuPC : public APlayerController
{
	GENERATED_BODY()
	
public:		// 변수
	UPROPERTY()
	FTimerHandle TimeReverse;

	class UC_ReverseGI* GI;

public:		// 함수
	virtual void BeginPlay() override;

	UFUNCTION()
	void DoReverse();
	UFUNCTION()
	void DoUnReverse();
	
};
