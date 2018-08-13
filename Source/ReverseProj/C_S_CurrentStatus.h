// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_S_CurrentStatus.generated.h"

USTRUCT(BlueprintType)
struct FC_S_Position {
	GENERATED_USTRUCT_BODY()

		FC_S_Position(FVector NewLocation = FVector(0.f,0.f,0.f), FQuat NewRotation = FQuat(0.f,0.f,0.f,0.f)) : Location(NewLocation), Rotation(NewRotation) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuat Rotation;
};

USTRUCT(BlueprintType)
struct FC_S_Velocity {
	GENERATED_USTRUCT_BODY()

		FC_S_Velocity(FVector NewDegree = FVector(0.f,0.f,0.f), FVector NewScale=FVector(0.f,0.f,0.f)) : Degree(NewDegree), Scale(NewScale) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Degree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Scale;
};