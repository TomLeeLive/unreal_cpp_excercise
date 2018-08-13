// Fill out your copyright notice in the Description page of Project Settings.

#include "MyRocket.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMyRocket::AMyRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Mesh = CreateDefaultSubobject < UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Box);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Rocket(TEXT("StaticMesh'/Game/P38/Models/SM_Rocket.SM_Rocket'"));

	if (SM_Rocket.Succeeded())
	{
		Mesh->SetStaticMesh(SM_Rocket.Object);
	}

	Mesh->AddLocalRotation(FRotator(-90, 0, 0));

	Movement = CreateDefaultSubobject < UProjectileMovementComponent>(TEXT("Movement"));

	Movement->InitialSpeed = 200.0f;
	Movement->MaxSpeed = 200.0f;
	Movement->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AMyRocket::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

