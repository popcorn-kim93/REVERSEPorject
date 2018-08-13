// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_ReverseGI.h"
#include "C_S_CurrentStatus.h"
#include "C_Movable.generated.h"

UCLASS()
class REVERSEPROJ_API AC_Movable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Movable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:		// 변수
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

	class UC_ReverseGI* GI;

	TArray<FC_S_Position> Positions;
	TArray<FC_S_Velocity> Velocitys;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool Reversable;

public:		// 함수
	

protected:
	
};
