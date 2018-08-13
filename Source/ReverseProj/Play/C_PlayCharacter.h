// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_ReverseGI.h"
#include "C_PlayCharacter.generated.h"

UCLASS()
class REVERSEPROJ_API AC_PlayCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_PlayCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:		// 변수
	UPROPERTY(VisibleANywhere, BlueprintReadWrite)
	class UC_ReverseGI* GI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float WalkSpeed;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float RuningSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RunningRatio;

public:		// 함수
	void DoReverse();

	void UndoReverse();

	void DoSprint();

	void UndoSprint();

	UFUNCTION(BlueprintImplementableEvent)
	void TurnOnPostProcess();
	UFUNCTION(BlueprintImplementableEvent)
	void TurnOffPostProcess();

};
