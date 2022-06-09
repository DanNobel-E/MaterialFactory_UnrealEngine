// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GegGeneralActor.generated.h"

UCLASS()
class GEOFACTORY_API AGegGeneralActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGegGeneralActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category="Custom Property")
	UStaticMeshComponent* MyStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Custom Property")
		UMaterialInstanceDynamic* MI_Instance_01;

	UPROPERTY(EditAnywhere)
		UTexture2D* MyText2D;

	UPROPERTY(EditAnywhere)
		FName TextureName;

};
