// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRocket.generated.h"

UCLASS()
class UNREAL_CPP_API AMyRocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyRocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Collision)
		class UBoxComponent* Box;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Rocket)
		class UStaticMeshComponent* Mesh;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Movement)
		class UProjectileMovementComponent* Movement;
};
