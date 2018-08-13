// Fill out your copyright notice in the Description page of Project Settings.

#include "C_PlayCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AC_PlayCharacter::AC_PlayCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WalkSpeed = 600.f;
	RunningRatio = 2.f;
}

// Called when the game starts or when spawned
void AC_PlayCharacter::BeginPlay()
{
	Super::BeginPlay();

	GI = Cast<UC_ReverseGI>(GetGameInstance());
	if (!(GI->IsValidLowLevel()))
	{
		UE_LOG(LogClass, Warning, TEXT("GI Cast Error, Fatal Error!!!"));
	}

	RuningSpeed = WalkSpeed * RunningRatio;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

// Called every frame
void AC_PlayCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_PlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("K_Reverse"), IE_Pressed, this, &AC_PlayCharacter::DoReverse);
	PlayerInputComponent->BindAction(TEXT("K_Reverse"), IE_Released, this, &AC_PlayCharacter::UndoReverse);
	PlayerInputComponent->BindAction(TEXT("K_Sprint"), IE_Pressed, this, &AC_PlayCharacter::DoSprint);
	PlayerInputComponent->BindAction(TEXT("K_Sprint"), IE_Released, this, &AC_PlayCharacter::UndoSprint);
}

void AC_PlayCharacter::DoReverse() {
	if (GI) {
		GI->ReverseActivate();
	}

	TurnOnPostProcess();
}

void AC_PlayCharacter::UndoReverse() {
	if (GI) {
		GI->ReverseDeActivate();
	}
	
	TurnOffPostProcess();
}

void AC_PlayCharacter::DoSprint() {
	GetCharacterMovement()->MaxWalkSpeed = RuningSpeed;
}

void AC_PlayCharacter::UndoSprint() {
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}