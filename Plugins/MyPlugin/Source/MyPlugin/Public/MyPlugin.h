// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ContentBrowserModule.h"
#include "Engine/StaticMeshActor.h"
#include "Factories/MaterialFactoryNew.h"
#include "ImageUtils.h"
#include "LevelEditor.h"
#include "Materials/MaterialExpressionConstant2Vector.h"
#include "Materials/MaterialExpressionScalarParameter.h"
#include "Materials/MaterialExpressionCosine.h"
#include "Materials/MaterialExpressionSine.h"
#include "Materials/MaterialExpressionDivide.h"
#include "Materials/MaterialExpressionSubtract.h"
#include "Materials/MaterialExpressionMultiply.h"
#include "Materials/MaterialExpressionAdd.h"
#include "Materials/MaterialExpressionVectorParameter.h"
#include "Materials/MaterialExpressionTime.h"
#include "Materials/MaterialExpressionPanner.h"
#include "Materials/MaterialExpressionTextureSampleParameter2D.h"
#include "Materials/MaterialExpressionWorldPosition.h"
#include "Misc/MessageDialog.h"
#include "Misc/FileHelper.h"
#include "ScopedTransaction.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "Factories/WorldFactory.h"
#include "BombermanWorldFactory.h"


class MYPLUGIN_API FMyPluginModule : public IModuleInterface, public FSelfRegisteringExec
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void CreateMenuBar(FMenuBarBuilder& MenuBarBuilder);
	void PopolateMenuBar(FMenuBuilder& MenuBuilder, const TArray<AActor*> InActors);

	void PrintLogMessageFromMenuBar(const TArray<AActor*> InActors);
	void PrintStringFromMenuBar(const FString Msg);

	TSharedRef<FExtender> GenerateActorMenu(const TSharedRef<FUICommandList> CommandList, const TArray<AActor*> Actors);

	void PopulateContentBrowser(FMenuBuilder& MenuBuilder, const TArray<FAssetData> Data);
	void ModifyTexture(const TArray<FAssetData> Data);
	TSharedRef<FExtender> ExtendContentBrowser(const TArray<FAssetData>& Data);

	bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);

	UMaterialExpressionVectorParameter* MakeColorMaterial(UMaterial* NewMaterial, FLinearColor InColor);
	UMaterialExpressionTextureSampleParameter2D* MakeTextureMaterial(UMaterial* NewMaterial, UMaterialExpressionVectorParameter* BaseColor, UTexture* InTexture);
	UMaterialExpressionPanner* MakeTextureModifiedMaterial(UMaterial* NewMaterial, UMaterialExpressionConstant2Vector* TextureOffset, UMaterialExpressionConstant2Vector* TextureScale, FVector2D Offset, FVector2D Scale);
	void MakeAnimatedMaterial(UMaterial* NewMaterial, UMaterialExpressionPanner* TexturePanner, UMaterialExpressionTextureSampleParameter2D* Texture, UMaterialExpressionConstant2Vector* TextureOffset, UMaterialExpressionConstant2Vector* TextureScale);
	void MakeGlowMaterial(UMaterial* NewMaterial, FLinearColor InColor, float InPower, float InSpeed);
	void MakePulseMaterial(UMaterial* NewMaterial, float InSpeed);

	FLinearColor ParseColor(FString& Value);


};
