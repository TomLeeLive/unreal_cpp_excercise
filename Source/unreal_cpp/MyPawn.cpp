// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
//#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MyRocket.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	P38 = CreateDefaultSubobject < UStaticMeshComponent>(TEXT("P38"));
	P38->SetupAttachment(Box);

	Left = CreateDefaultSubobject < UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(P38);

	Right = CreateDefaultSubobject < UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(P38);

	SpringArm = CreateDefaultSubobject < USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);

	Camera = CreateDefaultSubobject < UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Movement = CreateDefaultSubobject < UFloatingPawnMovement>(TEXT("Movement"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_P38(TEXT("StaticMesh'/Game/P38/Models/SM_P38_Body.SM_P38_Body'"));

	if (SM_P38.Succeeded())
	{
		P38->SetStaticMesh(SM_P38.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("StaticMesh'/Game/P38/Models/SM_P38_Propeller.SM_P38_Propeller'"));

	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	//위치조정
	Left->AddLocalOffset(FVector(37,20,0.7f));
	Right->AddLocalOffset(FVector(37, -20, 0.7f));
	
	
	Box->SetBoxExtent(FVector(42.7f,39.3f,39.3f));

	UE_LOG(LogClass, Warning, TEXT("안녕하세요 %d"),1234);

	Movement->MaxSpeed = 200.0f;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Left->AddLocalRotation(FRotator(0,0,1080*DeltaTime));
	Right->AddLocalRotation(FRotator(0, 0, 1080 * DeltaTime));

	AddMovementInput(GetActorForwardVector());
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPawn::Roll);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPawn::Fire);
}

void AMyPawn::Pitch(float AxisValue)
{
	AddActorLocalRotation(FRotator(AxisValue*60 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0, 0));
}

void AMyPawn::Roll(float AxisValue)
{
	AddActorLocalRotation(FRotator(0, 0, AxisValue*60 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
}

void AMyPawn::Fire()
{
	GetWorld()->SpawnActor<AMyRocket>(GetActorLocation(),
		GetActorRotation());
}