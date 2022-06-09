// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Factories/WorldFactory.h"
#include "ImageUtils.h"
#include <Editor/UnrealEd/Classes/ThumbnailRendering/WorldThumbnailInfo.h>
#include "BombermanWorldFactory.generated.h"

/**
 * 
 */
UCLASS()
class GEOFACTORY_API UBombermanWorldFactory : public UFactory
{
	GENERATED_BODY()
	
public:

	UBombermanWorldFactory(const FObjectInitializer& ObjectInitializer);
	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;


	UPROPERTY(EditAnywhere)
	TSubclassOf<AStaticMeshActor> Floor;

};
