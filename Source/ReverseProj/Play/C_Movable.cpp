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
	if (!(GI->IsValidLowLevel()))
	{
		UE_LOG(LogClass, Warning, TEXT("GameInstance Cast Fail! Fatal Error!!!"));
	}
}

// Called every frame
void AC_Movable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Reversable)
	{
		if (GI)
		{
			if (GI->GetReverseStatus())
			{
				FTransform TempTransform;
				if (Positions.IsValidIndex(Positions.Num() - 1))
				{
					TempTransform.SetLocation(Positions.Last().Location);
					TempTransform.SetRotation(Positions.Last().Rotation);
					TempTransform.SetScale3D(GetActorScale());
				}
				Mesh->SetWorldTransform(TempTransform);
				// ������ �ε����� 0���� ū�� Ȯ��.
				if (Positions.Num() > 1)
				{
					// ������� ������ �ε��� ����.
					Positions.RemoveAt(Positions.Num() - 1);
				}

				// Velocity Set.

				if (Velocitys.IsValidIndex(Velocitys.Num() - 1))
				{
					// set physics liner velocity
					Mesh->SetPhysicsLinearVelocity(Velocitys.Last().Degree);
					// set physics Angular velocity
					Mesh->SetPhysicsAngularVelocityInDegrees(Velocitys.Last().Scale);
				}

				// ������ �ε����� 0���� ���� Ȯ��.
				if (Velocitys.Num() > 1)
				{
					// �ƴҰ�� ������ �ε��� ����.
					Velocitys.RemoveAt(Velocitys.Num() - 1);
				}
			}
			else
			{									// �ǵ����� ��Ȱ��ȭ.
												// �迭�� �ʹ� ������°��� ����.
				if (Positions.Num() >= 5000)
				{
					Positions.RemoveAt(0);
				}
				if (Velocitys.Num() >= 5000)
				{
					Velocitys.RemoveAt(0);
				}
				// Location ����.
				FC_S_Position TempPos = FC_S_Position(Mesh->GetComponentToWorld().GetLocation(), Mesh->GetComponentToWorld().GetRotation());
				Positions.Emplace(TempPos);

				// Velocity ����.
				FC_S_Velocity TempVel = FC_S_Velocity(Mesh->GetPhysicsLinearVelocity(), Mesh->GetPhysicsAngularVelocityInDegrees());
				Velocitys.Emplace(TempVel);
			}
		}
	}
	else
	{
		Mesh->SetMobility(EComponentMobility::Static);
	}
}

