// Fill out your copyright notice in the Description page of Project Settings.

#include "C_Movable.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AC_Movable::AC_Movable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Mesh->SetSimulatePhysics(true);

	Reversable = true;
}

// Called when the game starts or when spawned
void AC_Movable::BeginPlay()
{
	Super::BeginPlay();
	
	GI = Cast<UC_ReverseGI>(GetGameInstance());
	if (!(GI->IsValidLowLevel())) {
		UE_LOG(LogClass, Warning, TEXT("GameInstance Cast Fail! Fatal Error!!!"));
	}
}

// Called every frame
void AC_Movable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Reversable) {
		if (GI) {
			if (GI->GetReverseStatus()) {		// 되돌리기 활성화.
												// Location Set.

												//Position array 가져 옴.
												//마지막 Index 를 얻어옴.

												// SetworldTransfrom(without Scale)
				FTransform TempTransform;
				if (Positions.IsValidIndex(Positions.Num() - 1)) {
					TempTransform.SetLocation(Positions.Last().Location);
					TempTransform.SetRotation(Positions.Last().Rotation);
					TempTransform.SetScale3D(GetActorScale());
				}
				Mesh->SetWorldTransform(TempTransform);
				// 마지막 인덱스가 0보다 큰지 확인.
				if (Positions.Num() > 1) {
					// 맞을경우 마지막 인덱스 삭제.
					Positions.RemoveAt(Positions.Num() - 1);
				}

				// Velocity Set.

				if (Velocitys.IsValidIndex(Velocitys.Num() - 1)) {
					// set physics liner velocity
					Mesh->SetPhysicsLinearVelocity(Velocitys.Last().Degree);
					// set physics Angular velocity
					Mesh->SetPhysicsAngularVelocityInDegrees(Velocitys.Last().Scale);
				}

				// 마지막 인덱스가 0보다 킅지 확인.
				if (Velocitys.Num() > 1) {
					// 아닐경우 마지막 인덱스 삭제.
					Velocitys.RemoveAt(Velocitys.Num() - 1);
				}


			}
			else {								// 되돌리기 비활성화.

												// 배열이 너무 길어지는것을 방지.
				if (Positions.Num() >= 5000) {
					Positions.RemoveAt(0);
				}
				if (Velocitys.Num() >= 5000) {
					Velocitys.RemoveAt(0);
				}

				// Location 저장.
				FC_S_Position TempPos = FC_S_Position(Mesh->GetComponentToWorld().GetLocation(), Mesh->GetComponentToWorld().GetRotation());
				Positions.Emplace(TempPos);

				// Velocity 저장.
				FC_S_Velocity TempVel = FC_S_Velocity(Mesh->GetPhysicsLinearVelocity(), Mesh->GetPhysicsAngularVelocityInDegrees());
				Velocitys.Emplace(TempVel);
			}
		}
	}
	else {
		Mesh->SetMobility(EComponentMobility::Static);
	}
	
}

