// Fill out your copyright notice in the Description page of Project Settings.


#include "GegGeneralActor.h"

// Sets default values
AGegGeneralActor::AGegGeneralActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = MyStaticMesh;

	TextureName = FName("DefaultTextureName");
}

// Called when the game starts or when spawned
void AGegGeneralActor::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInterface* MaterialInterface = MyStaticMesh->GetMaterial(0);
	MI_Instance_01 = UMaterialInstanceDynamic::Create(MaterialInterface, this);
	MI_Instance_01->SetTextureParameterValue(TextureName, MyText2D);
	MyStaticMesh->SetMaterial(0, MI_Instance_01);
}

// Called every frame
void AGegGeneralActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

