// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanWorldFactory.h"

UBombermanWorldFactory::UBombermanWorldFactory(const FObjectInitializer& ObjectInitializer)
{
	bCreateNew = true;
	SupportedClass = UWorld::StaticClass();
}

UObject* UBombermanWorldFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	const bool bAddToRoot = false;
	UWorld* NewWorld = UWorld::CreateWorld(EWorldType::Inactive, false, InName, Cast<UPackage>(InParent), bAddToRoot,ERHIFeatureLevel::Num);
	GEditor->InitBuilderBrush(NewWorld);
	NewWorld->SetFlags(Flags);
	NewWorld->ThumbnailInfo = NewObject<UWorldThumbnailInfo>(NewWorld, NAME_None, RF_Transactional);

	UTexture2D* Texture = FImageUtils::ImportFileAsTexture2D(Filename);
	
	int32 Width = Texture->GetSizeX();
	int32 Height = Texture->GetSizeY();

	if (Floor)
	{
		FTransform Transform;
		Transform.SetLocation(FVector(0, 0, 0));
		Transform.SetScale3D(FVector(Width * 100, Height * 100, 100));
		NewWorld->SpawnActor<AStaticMeshActor>(Floor,Transform);

	}


	return NewWorld;
}