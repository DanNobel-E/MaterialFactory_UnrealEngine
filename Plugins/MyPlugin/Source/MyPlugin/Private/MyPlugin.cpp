// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyPlugin.h"

#define LOCTEXT_NAMESPACE "FMyPluginModule"

void FMyPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FLevelEditorModule& LevelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	// menu bar
	TSharedRef<FExtender> Extender = MakeShared<FExtender>();
	Extender->AddMenuBarExtension(FName("Window"), EExtensionHook::After, nullptr, FMenuBarExtensionDelegate::CreateRaw(this, &FMyPluginModule::CreateMenuBar));
	LevelEditor.GetMenuExtensibilityManager()->AddExtender(Extender);

	// menu actor
	LevelEditor.GetAllLevelViewportContextMenuExtenders().Add(FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateRaw(this, &FMyPluginModule::GenerateActorMenu));

	FContentBrowserModule& ContentBrowser = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	ContentBrowser.GetAllAssetViewContextMenuExtenders().Add(FContentBrowserMenuExtender_SelectedAssets::CreateRaw(this, &FMyPluginModule::ExtendContentBrowser));

}

TSharedRef<FExtender> FMyPluginModule::ExtendContentBrowser(const TArray<FAssetData>& Data)
{
	TSharedRef<FExtender> Extender = MakeShared<FExtender>();
	Extender->AddMenuExtension(FName("CommonAssetActions"), EExtensionHook::After, nullptr, FMenuExtensionDelegate::CreateRaw(this, &FMyPluginModule::PopulateContentBrowser, Data));
	return Extender;
}

void FMyPluginModule::ModifyTexture(const TArray<FAssetData> Data)
{
	for (const FAssetData& Datum : Data)
	{
		UObject* Object = Datum.GetAsset();
		UTexture2D* Texture = Cast<UTexture2D>(Object);

		if (Texture)
		{
			UE_LOG(LogTemp, Error, TEXT("Name: %d"), Texture->GetSizeX());
			
			uint8* MipData = Texture->Source.LockMip(0);
			for (int32 x = 0; x < Texture->GetSizeX() * Texture->GetSizeY() * 4; x+=4)
			{
				MipData[x + 2] = 255;
			}
			Texture->Source.UnlockMip(0);
			Texture->PostEditChange();
			Texture->MarkPackageDirty();
		}
	}
}

void FMyPluginModule::PopulateContentBrowser(FMenuBuilder& MenuBuilder, const TArray<FAssetData> Data)
{
	for (const FAssetData& Datum : Data)
	{
		if (Datum.AssetClass != FName("Texture2D"))
		{
			return;
		}
	}

	MenuBuilder.BeginSection(FName("FirstSection"), FText::FromString("FirstSectionMenu"));
	MenuBuilder.AddMenuEntry(FText::FromString("MyAction"), FText::FromString("Do first action!"), FSlateIcon(), FUIAction(FExecuteAction::CreateRaw(this, &FMyPluginModule::ModifyTexture, Data)));
	MenuBuilder.EndSection();
}

TSharedRef<FExtender> FMyPluginModule::GenerateActorMenu(const TSharedRef<FUICommandList> CommandList, const TArray<AActor*> Actors)
{
	TSharedRef<FExtender> Extender = MakeShared<FExtender>();

	Extender->AddMenuExtension(FName("ActorAsset"), EExtensionHook::After, CommandList, FMenuExtensionDelegate::CreateRaw(this, &FMyPluginModule::PopolateMenuBar, Actors));
	return Extender;
}

void FMyPluginModule::ShutdownModule()
{
	
}

void FMyPluginModule::CreateMenuBar(FMenuBarBuilder& MenuBarBuilder)
{
	//MenuBarBuilder.AddPullDownMenu(FText::FromString("CustomMenu"), FText::FromString("Menu Custom"), FNewMenuDelegate::CreateRaw(this, &FMyPluginModule::PopolateMenuBar), FName("GegMenu"));
}

//void FMyPluginModule::PopolateMenuBar(FMenuBuilder& MenuBuilder)
//{
//	MenuBuilder.BeginSection(FName("FirstLevel"), FText::FromString("FirstSectionMenu"));
//	MenuBuilder.AddMenuEntry(FText::FromString("Voice_001"), FText::FromString("Voice 001 Tooltip"), FSlateIcon(), FUIAction(FExecuteAction::CreateRaw(this, &FMyPluginModule::PrintLogMessageFromMenuBar)));
//	MenuBuilder.AddMenuEntry(FText::FromString("Voice_002"), FText::FromString("Voice 002 Tooltip"), FSlateIcon(), FUIAction());
//	MenuBuilder.AddMenuEntry(FText::FromString("Voice_003"), FText::FromString("Voice 003 Tooltip"), FSlateIcon(), FUIAction());
//	MenuBuilder.AddSeparator();
//	MenuBuilder.AddMenuEntry(FText::FromString("Voice_004"), FText::FromString("Voice 004 Tooltip"), FSlateIcon(), FUIAction());
//	MenuBuilder.AddMenuEntry(FText::FromString("Voice_005"), FText::FromString("Voice 005 Tooltip"), FSlateIcon(), FUIAction());
//	MenuBuilder.EndSection();
//
//	MenuBuilder.BeginSection(FName("SecondLevel"), FText::FromString("Second Section Menu"));
//	MenuBuilder.AddMenuEntry(FText::FromString("Voice_001"), FText::FromString("Voice 001 Tooltip"), FSlateIcon(), FUIAction());
//	MenuBuilder.AddMenuEntry(FText::FromString("Voice_002"), FText::FromString("Voice 002 Tooltip"), FSlateIcon(), FUIAction());
//	MenuBuilder.AddMenuEntry(FText::FromString("Voice_003"), FText::FromString("Voice 003 Tooltip"), FSlateIcon(), FUIAction());
//	MenuBuilder.AddSeparator();
//	MenuBuilder.AddMenuEntry(FText::FromString("Voice_004"), FText::FromString("Voice 004 Tooltip"), FSlateIcon(), FUIAction());
//	MenuBuilder.AddMenuEntry(FText::FromString("Voice_005"), FText::FromString("Voice 005 Tooltip"), FSlateIcon(), FUIAction(FExecuteAction::CreateRaw(this, &FMyPluginModule::PrintStringFromMenuBar, FString("Message to Delegate"))));
//	MenuBuilder.EndSection();
//}

void FMyPluginModule::PopolateMenuBar(FMenuBuilder& MenuBuilder, const TArray<AActor*> InActors)
{
	// controllo opzionale per la gestione di sotto voci
	for (AActor* Actor : InActors)
	{
		if (!Actor->IsA<AStaticMeshActor>())
		{
			return;
		}
	}
	MenuBuilder.BeginSection(FName("FirstLevel"), FText::FromString("FirstSectionMenu"));
	MenuBuilder.AddMenuEntry(FText::FromString("Voice_001"), FText::FromString("Voice 001 Tooltip"), FSlateIcon(), FUIAction(FExecuteAction::CreateRaw(this, &FMyPluginModule::PrintLogMessageFromMenuBar, InActors)));
	MenuBuilder.AddMenuEntry(FText::FromString("Voice_002"), FText::FromString("Voice 002 Tooltip"), FSlateIcon(), FUIAction());
	MenuBuilder.AddMenuEntry(FText::FromString("Voice_003"), FText::FromString("Voice 003 Tooltip"), FSlateIcon(), FUIAction());
	MenuBuilder.AddSeparator();
	MenuBuilder.AddMenuEntry(FText::FromString("Voice_004"), FText::FromString("Voice 004 Tooltip"), FSlateIcon(), FUIAction());
	MenuBuilder.AddMenuEntry(FText::FromString("Voice_005"), FText::FromString("Voice 005 Tooltip"), FSlateIcon(), FUIAction());
	MenuBuilder.EndSection();

	MenuBuilder.BeginSection(FName("SecondLevel"), FText::FromString("Second Section Menu"));
	MenuBuilder.AddMenuEntry(FText::FromString("Voice_001"), FText::FromString("Voice 001 Tooltip"), FSlateIcon(), FUIAction());
	MenuBuilder.AddMenuEntry(FText::FromString("Voice_002"), FText::FromString("Voice 002 Tooltip"), FSlateIcon(), FUIAction());
	MenuBuilder.AddMenuEntry(FText::FromString("Voice_003"), FText::FromString("Voice 003 Tooltip"), FSlateIcon(), FUIAction());
	MenuBuilder.AddSeparator();
	MenuBuilder.AddMenuEntry(FText::FromString("Voice_004"), FText::FromString("Voice 004 Tooltip"), FSlateIcon(), FUIAction());
	MenuBuilder.AddMenuEntry(FText::FromString("Voice_005"), FText::FromString("Voice 005 Tooltip"), FSlateIcon(), FUIAction(FExecuteAction::CreateRaw(this, &FMyPluginModule::PrintStringFromMenuBar, FString("Message to Delegate"))));
	MenuBuilder.EndSection();
}


void FMyPluginModule::PrintLogMessageFromMenuBar(const TArray<AActor*> InActors)
{
	UE_LOG(LogTemp, Error, TEXT("Custom log message from menu bar action"));

	for (AActor* Actor:InActors)
	{
		//FScopedTransaction
		const FScopedTransaction Transaction(FText::FromString("Move Actor on Z"));
		Actor->Modify();
		Actor->AddActorLocalOffset(FVector(0, 0, 100));
		Actor->PostEditChange();
	}
}

void FMyPluginModule::PrintStringFromMenuBar(const FString Msg)
{
	FText TitleMsg = FText::FromString("Custom Dialog Message");
	FMessageDialog::Open(EAppMsgType::OkCancel, FText::FromString(Msg), &TitleMsg);
}

bool FMyPluginModule::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{

	if (FParse::Command(&Cmd, TEXT("newmaterial")))
	{
		UMaterialFactoryNew* NewMaterial = NewObject<UMaterialFactoryNew>();
		// in "prod": controllare che asset non esista...

		uint64 SuffixAssetName = FPlatformTime::Cycles64();
		FString AssetName = FString::Printf(TEXT("M_Dummy_%llu"), SuffixAssetName);
		UPackage* Package = CreatePackage(*FString::Printf(TEXT("/Game/%s"), *AssetName));

		UObject* NewMaterialObject = NewMaterial->FactoryCreateNew(NewMaterial->SupportedClass, Package, *AssetName, EObjectFlags::RF_Standalone | EObjectFlags::RF_Public, nullptr, GWarn);
		FAssetRegistryModule::AssetCreated(NewMaterialObject);
		
		UMaterial* MaterialCasted = Cast<UMaterial>(NewMaterialObject);
		
		// inizio transazione sul materiale
		MaterialCasted->Modify();

		UMaterialExpressionVectorParameter* VectorParameter = NewObject<UMaterialExpressionVectorParameter>(MaterialCasted);
		VectorParameter->DefaultValue = FLinearColor::Blue;
		VectorParameter->ParameterName = TEXT("BaseColorBlue");
		VectorParameter->MaterialExpressionEditorX = -400;

		UMaterialExpressionMultiply* MaterialMulplier = NewObject<UMaterialExpressionMultiply>(MaterialCasted);
		MaterialMulplier->A.Expression = VectorParameter;
		MaterialMulplier->ConstB = 2;
		MaterialMulplier->MaterialExpressionEditorX = -200;

		MaterialCasted->BaseColor.Expression = MaterialMulplier;
		MaterialCasted->Expressions.Add(VectorParameter);		
		MaterialCasted->Expressions.Add(MaterialMulplier);		

		MaterialCasted->PostEditChange();
		MaterialCasted->MarkPackageDirty();

		GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(MaterialCasted);

		return true;

	}else if (FParse::Command(&Cmd, TEXT("makematerial")))
	{
		UMaterialFactoryNew* MaterialFactory = NewObject<UMaterialFactoryNew>();
		uint64 SuffixAssetName = FPlatformTime::Cycles64();
		FString AssetName = FString::Printf(TEXT("M_Dummy_%llu"), SuffixAssetName);
		UPackage* Package = CreatePackage(*FString::Printf(TEXT("/Game/%s"), *AssetName));
		UObject* NewMaterialObject = MaterialFactory->FactoryCreateNew(MaterialFactory->SupportedClass, Package, *AssetName, EObjectFlags::RF_Standalone | EObjectFlags::RF_Public, nullptr, GWarn);
		FAssetRegistryModule::AssetCreated(NewMaterialObject);
		UMaterial* NewMaterial = Cast<UMaterial>(NewMaterialObject);

		if (FParse::Command(&Cmd, TEXT("random")))
		{

			NewMaterial->Modify();

			//BaseColor
			UMaterialExpressionVectorParameter* BaseColor= MakeColorMaterial(NewMaterial, FLinearColor::MakeRandomColor());

			bool TextureMaterial = FMath::RandBool();

			if (!TextureMaterial)
			{
				NewMaterial->BaseColor.Expression = BaseColor;

			}
			else
			{
				//Texture
				UMaterialExpressionTextureSampleParameter2D* Texture = MakeTextureMaterial(NewMaterial, BaseColor, nullptr);

				bool TextureModifiers = FMath::RandBool();


				if (TextureModifiers)
				{
					UMaterialExpressionConstant2Vector* TextureOffset = NewObject<UMaterialExpressionConstant2Vector>(NewMaterial);
					UMaterialExpressionConstant2Vector* TextureScale= NewObject<UMaterialExpressionConstant2Vector>(NewMaterial);

					FVector2D Offset = FVector2D(FMath::FRand(), FMath::FRand());
					float ScaleVal = FMath::FRandRange(0.1, 10);
					FVector2D Scale = FVector2D(ScaleVal,ScaleVal);


					UMaterialExpressionPanner* TexturePanner =  MakeTextureModifiedMaterial(NewMaterial, TextureOffset,TextureScale,Offset,Scale);

					bool AnimateTexture = FMath::RandBool();

					if (!AnimateTexture)
					{
						MakeAnimatedMaterial(NewMaterial, TexturePanner, Texture,TextureOffset,TextureScale);
					}
					else
					{
						UMaterialExpressionTime* Time = NewObject<UMaterialExpressionTime>(NewMaterial);
						Time->MaterialExpressionEditorX = -1500;
						Time->MaterialExpressionEditorY = -400;

						NewMaterial->Expressions.Add(Time);

						UMaterialExpressionMultiply* MultPanner_Scale = NewObject<UMaterialExpressionMultiply>(NewMaterial);

						MultPanner_Scale->MaterialExpressionEditorX = -800;
						MultPanner_Scale->MaterialExpressionEditorY = -200;

						NewMaterial->Expressions.Add(MultPanner_Scale);

						TexturePanner->Time.Expression = Time;
						TexturePanner->Speed.Expression = TextureOffset;

						MultPanner_Scale->A.Expression = TexturePanner;
						MultPanner_Scale->B.Expression = TextureScale;


						Texture->Coordinates.Expression = MultPanner_Scale;

					}

				}


			}
			
			bool GlowMaterial = FMath::RandBool();

			if (GlowMaterial)
			{
				MakeGlowMaterial(NewMaterial,FLinearColor::MakeRandomColor(),FMath::Floor(FMath::RandRange(10,100)), FMath::RandRange(0.1, 5));

			}

			bool PulseMaterial = FMath::RandBool();

			if (PulseMaterial)
			{
				MakePulseMaterial(NewMaterial, FMath::RandRange(0.1, 5));
			}

			NewMaterial->PostEditChange();
			NewMaterial->MarkPackageDirty();

			GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(NewMaterial);
			return true;
		}
		else if (FParse::Command(&Cmd, TEXT("from")))
		{
			FString FilePath= "";
			FString TexturePath ="";

			FString Command = FString(Cmd);

			Command.Split(" ", &FilePath, &TexturePath);

			if (FilePath == "")
			{
				if (Command == "")
				{
					return false;

				}
			}
			FilePath = Command;


			TArray<FString> File;
			FFileHelper::LoadFileToStringArray(File, *FilePath);

			FString ColorLabel = "color";
			FLinearColor Color= FLinearColor::White;

			FString TextureLabel = "texture";
			FString TextureNameDefaultLabel = "default";
			UTexture* InTexture= nullptr;
			bool IsTextured = false;

			bool IsTextureModified = false;
			FVector2D Offset = FVector2D::ZeroVector;
			FVector2D Scale = FVector2D(1, 1);

			FString TextureAnimatedLabel = "anim";
			bool IsTextureAnimated= false;

			FString GlowLabel = "glow";
			bool IsGlowing = false;
			FLinearColor GlowColor = FLinearColor::White;
			float GlowPower = 10;
			float GlowSpeed = 1;


			FString PulseLabel = "pulse";
			bool IsPulsing = false;
			float PulseSpeed = 1;


			for (size_t Index = 0; Index < File.Num(); Index++)
			{
				FString Label;
				FString Value;

				File[Index].Split(" ", &Label, &Value);
				Label = Label.ToLower();

				if (Label.Len() <= 0)
				{
					Label = File[Index];
				}

				if (Label == ColorLabel)
				{
					Color = ParseColor(Value);

				}
				else if (Label == TextureLabel)
				{
					if (TexturePath.Len() > 0)
					{

						//Add texture loading logic

					}
					else
					{
						FString TextureName = "";
						Value.Split(" ", &TextureName, &Value);

						IsTextured = true;
						int32 TryParse = -1;

						


						if (TextureName.Len() > 0)
						{
							TryParse = FCString::Atof(*TextureName);


							if (TextureName.ToLower() == TextureNameDefaultLabel || TryParse>0)
							{
								TArray<FString> TransformArr;
								TArray<float> TransformValuesArr;
								TransformArr.SetNumZeroed(4);
								TransformValuesArr.SetNumZeroed(4);

								for (size_t i = 0; i < 4; i++)
								{
									if (i == 0)
									{
										if (TryParse > 0)
										{
											TransformValuesArr[i] = TryParse;
											continue;
										}
									}

									if ((Value.Split((" "), &TransformArr[i], &Value)))
									{


										TransformValuesArr[i] = FCString::Atof(*TransformArr[i]);

									}
									else if (Value.Len() > 0)
									{
										TransformArr[i] = Value;
										TransformValuesArr[i] = FCString::Atof(*TransformArr[i]);
									}

								}

								FVector2D ScaleVal = FVector2D(TransformValuesArr[0], TransformValuesArr[1]);
								FVector2D OffsetVal = FVector2D(TransformValuesArr[2], TransformValuesArr[3]);

								if (ScaleVal.IsZero())
								{
									continue;
								}

								if (ScaleVal == FVector2D(1, 1) && OffsetVal.IsZero())
								{
									continue;
								}

								Scale = ScaleVal;
								Offset = OffsetVal;
								IsTextureModified = true;

							}
							//add texture load logic

						}
						else
						{
							continue;
						}

					}



				}
				else if (Label == TextureAnimatedLabel)
				{
					if (IsTextured)
					{

						IsTextureAnimated = Value.ToBool();

					}



				}
				else if (Label == GlowLabel)
				{
					FString Result;
					Value.Split(" ", &Result, &Value);

					IsGlowing = Value.ToBool();

					if (IsGlowing)
					{

						if (Value.Split(" ", &Result, &Value))
						{

							float PowerVal = FCString::Atof(*Result);

							if (PowerVal <= 0)
							{
								continue;
							}

							GlowPower = PowerVal;

							if (Value.Split(" ", &Result, &Value))
							{
								float SpeedVal = FCString::Atof(*Result);

								if (SpeedVal <= 0)
								{
									continue;
								}

								GlowSpeed = SpeedVal;

								GlowColor = ParseColor(Value);
							}
						}



					}



				}
				else if (Label == PulseLabel)
				{
					FString Result;
					Value.Split(" ", &Result, &Value);

					IsPulsing = Value.ToBool();

					if (IsPulsing)
					{

						float SpeedVal = FCString::Atof(*Value);

						if (SpeedVal > 0)
						{
							PulseSpeed = SpeedVal;
						}

					}


				}


			}

			NewMaterial->Modify();

			//BaseColor
			UMaterialExpressionVectorParameter* BaseColor = MakeColorMaterial(NewMaterial, Color);

			if (!IsTextured)
			{
				NewMaterial->BaseColor.Expression = BaseColor;

			}
			else
			{
				//Texture
				UMaterialExpressionTextureSampleParameter2D* Texture = MakeTextureMaterial(NewMaterial, BaseColor, InTexture);

				if (IsTextureModified)
				{
					UMaterialExpressionConstant2Vector* TextureOffset = NewObject<UMaterialExpressionConstant2Vector>(NewMaterial);
					UMaterialExpressionConstant2Vector* TextureScale = NewObject<UMaterialExpressionConstant2Vector>(NewMaterial);


					UMaterialExpressionPanner* TexturePanner = MakeTextureModifiedMaterial(NewMaterial, TextureOffset, TextureScale, Offset, Scale);

					if (!IsTextureAnimated)
					{
						MakeAnimatedMaterial(NewMaterial, TexturePanner, Texture, TextureOffset, TextureScale);
					}
					else
					{
						UMaterialExpressionTime* Time = NewObject<UMaterialExpressionTime>(NewMaterial);
						Time->MaterialExpressionEditorX = -1500;
						Time->MaterialExpressionEditorY = -400;

						NewMaterial->Expressions.Add(Time);

						UMaterialExpressionMultiply* MultPanner_Scale = NewObject<UMaterialExpressionMultiply>(NewMaterial);

						MultPanner_Scale->MaterialExpressionEditorX = -800;
						MultPanner_Scale->MaterialExpressionEditorY = -200;

						NewMaterial->Expressions.Add(MultPanner_Scale);

						TexturePanner->Time.Expression = Time;
						TexturePanner->Speed.Expression = TextureOffset;

						MultPanner_Scale->A.Expression = TexturePanner;
						MultPanner_Scale->B.Expression = TextureScale;


						Texture->Coordinates.Expression = MultPanner_Scale;

					}

				}


			}

		
			if (IsGlowing)
			{
				MakeGlowMaterial(NewMaterial, GlowColor, GlowPower, GlowSpeed);

			}


			if (IsPulsing)
			{
				MakePulseMaterial(NewMaterial, PulseSpeed);
			}

			NewMaterial->PostEditChange();
			NewMaterial->MarkPackageDirty();

			GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(NewMaterial);
			return true;


			return true;
		}

		return false;
	}

	return false;
}


UMaterialExpressionVectorParameter* FMyPluginModule::MakeColorMaterial(UMaterial* NewMaterial, FLinearColor InColor)
{
	UMaterialExpressionVectorParameter* BaseColor = NewObject<UMaterialExpressionVectorParameter>(NewMaterial);
	BaseColor->ParameterName = TEXT("BaseColor");

	BaseColor->DefaultValue = InColor;

	BaseColor->MaterialExpressionEditorX = -400;
	BaseColor->MaterialExpressionEditorY = 0;

	NewMaterial->Expressions.Add(BaseColor);

	return BaseColor;
}

UMaterialExpressionTextureSampleParameter2D* FMyPluginModule::MakeTextureMaterial(UMaterial* NewMaterial, UMaterialExpressionVectorParameter* BaseColor, UTexture* InTexture)
{
	UMaterialExpressionTextureSampleParameter2D* Texture = NewObject<UMaterialExpressionTextureSampleParameter2D>(NewMaterial);
	Texture->ParameterName = TEXT("Texture");

	if (InTexture)
	{
		Texture->SetParameterValue(FName(InTexture->GetName()), InTexture);
	}
	else
	{
		Texture->SetDefaultTexture();

	}

	Texture->MaterialExpressionEditorX = -400;
	Texture->MaterialExpressionEditorY = -250;

	NewMaterial->Expressions.Add(Texture);

	UMaterialExpressionMultiply* MultTexture_BaseColor = NewObject<UMaterialExpressionMultiply>(NewMaterial);

	MultTexture_BaseColor->MaterialExpressionEditorX = -150;
	MultTexture_BaseColor->MaterialExpressionEditorY = -100;

	NewMaterial->Expressions.Add(MultTexture_BaseColor);


	MultTexture_BaseColor->A.Expression = Texture;
	MultTexture_BaseColor->B.Expression = BaseColor;

	NewMaterial->BaseColor.Expression = MultTexture_BaseColor;

	return Texture;
}

UMaterialExpressionPanner* FMyPluginModule::MakeTextureModifiedMaterial(UMaterial* NewMaterial, UMaterialExpressionConstant2Vector* TextureOffset, UMaterialExpressionConstant2Vector* TextureScale, FVector2D Offset, FVector2D Scale)
{
	TextureOffset->R = Offset.X;
	TextureOffset->G = Offset.Y;

	TextureOffset->MaterialExpressionEditorX = -1500;
	TextureOffset->MaterialExpressionEditorY = -200;

	NewMaterial->Expressions.Add(TextureOffset);		// aggiunta del parametro al materiale


	TextureScale->R = Scale.X;
	TextureScale->G = Scale.Y;

	TextureScale->MaterialExpressionEditorX = -1200;
	TextureScale->MaterialExpressionEditorY = 0;

	NewMaterial->Expressions.Add(TextureScale);		// aggiunta del parametro al materiale



	UMaterialExpressionPanner* TexturePanner = NewObject<UMaterialExpressionPanner>(NewMaterial);

	TexturePanner->MaterialExpressionEditorX = -1200;
	TexturePanner->MaterialExpressionEditorY = -200;

	NewMaterial->Expressions.Add(TexturePanner);

	return TexturePanner;
}

void FMyPluginModule::MakeAnimatedMaterial(UMaterial* NewMaterial, UMaterialExpressionPanner* TexturePanner, UMaterialExpressionTextureSampleParameter2D* Texture, UMaterialExpressionConstant2Vector* TextureOffset, UMaterialExpressionConstant2Vector* TextureScale)
{
	UMaterialExpressionAdd* AddPanner_Offset = NewObject<UMaterialExpressionAdd>(NewMaterial);

	AddPanner_Offset->MaterialExpressionEditorX = -1000;
	AddPanner_Offset->MaterialExpressionEditorY = -200;

	NewMaterial->Expressions.Add(AddPanner_Offset);

	AddPanner_Offset->A.Expression = TexturePanner;
	AddPanner_Offset->B.Expression = TextureOffset;

	UMaterialExpressionMultiply* MultAdder_Scale = NewObject<UMaterialExpressionMultiply>(NewMaterial);

	MultAdder_Scale->MaterialExpressionEditorX = -800;
	MultAdder_Scale->MaterialExpressionEditorY = -100;

	NewMaterial->Expressions.Add(MultAdder_Scale);

	MultAdder_Scale->A.Expression = AddPanner_Offset;
	MultAdder_Scale->B.Expression = TextureScale;

	Texture->Coordinates.Expression = MultAdder_Scale;

}

void FMyPluginModule::MakeGlowMaterial(UMaterial* NewMaterial, FLinearColor InColor, float InPower, float InSpeed)
{
	UMaterialExpressionMultiply* MultColor_Mult = NewObject<UMaterialExpressionMultiply>(NewMaterial);

	MultColor_Mult->MaterialExpressionEditorX = -150;
	MultColor_Mult->MaterialExpressionEditorY = 300;

	NewMaterial->Expressions.Add(MultColor_Mult);

	NewMaterial->EmissiveColor.Expression = MultColor_Mult;

	UMaterialExpressionVectorParameter* GlowColor = NewObject<UMaterialExpressionVectorParameter>(NewMaterial);
	GlowColor->ParameterName = TEXT("GlowColor");

	GlowColor->DefaultValue = InColor;

	GlowColor->MaterialExpressionEditorX = -400;
	GlowColor->MaterialExpressionEditorY = 200;

	NewMaterial->Expressions.Add(GlowColor);

	UMaterialExpressionMultiply* MultCos_Power = NewObject<UMaterialExpressionMultiply>(NewMaterial);

	MultCos_Power->MaterialExpressionEditorX = -300;
	MultCos_Power->MaterialExpressionEditorY = 400;

	NewMaterial->Expressions.Add(MultCos_Power);

	MultColor_Mult->A.Expression = GlowColor;
	MultColor_Mult->B.Expression = MultCos_Power;

	UMaterialExpressionCosine* Cosine = NewObject<UMaterialExpressionCosine>(NewMaterial);

	Cosine->MaterialExpressionEditorX = -450;
	Cosine->MaterialExpressionEditorY = 400;

	NewMaterial->Expressions.Add(Cosine);

	UMaterialExpressionScalarParameter* GlowPower = NewObject<UMaterialExpressionScalarParameter>(NewMaterial);
	GlowPower->ParameterName = TEXT("GlowPower");

	GlowPower->DefaultValue = InPower;

	GlowPower->MaterialExpressionEditorX = -450;
	GlowPower->MaterialExpressionEditorY = 550;

	NewMaterial->Expressions.Add(GlowPower);

	MultCos_Power->A.Expression = Cosine;
	MultCos_Power->B.Expression = GlowPower;


	UMaterialExpressionMultiply* MultTime_Speed = NewObject<UMaterialExpressionMultiply>(NewMaterial);

	MultTime_Speed->MaterialExpressionEditorX = -600;
	MultTime_Speed->MaterialExpressionEditorY = 400;

	NewMaterial->Expressions.Add(MultTime_Speed);

	Cosine->Input.Expression = MultTime_Speed;

	UMaterialExpressionTime* Time = NewObject<UMaterialExpressionTime>(NewMaterial);
	Time->MaterialExpressionEditorX = -800;
	Time->MaterialExpressionEditorY = 400;

	NewMaterial->Expressions.Add(Time);

	UMaterialExpressionScalarParameter* GlowSpeed = NewObject<UMaterialExpressionScalarParameter>(NewMaterial);
	GlowSpeed->ParameterName = TEXT("GlowSpeed");

	GlowSpeed->DefaultValue = InSpeed;

	GlowSpeed->MaterialExpressionEditorX = -850;
	GlowSpeed->MaterialExpressionEditorY = 550;

	NewMaterial->Expressions.Add(GlowSpeed);

	MultTime_Speed->A.Expression = Time;
	MultTime_Speed->B.Expression = GlowSpeed;
}

void FMyPluginModule::MakePulseMaterial(UMaterial* NewMaterial, float InSpeed)
{
	UMaterialExpressionAdd* AddMult_One = NewObject<UMaterialExpressionAdd>(NewMaterial);

	AddMult_One->MaterialExpressionEditorX = -150;
	AddMult_One->MaterialExpressionEditorY = 550;

	AddMult_One->ConstB = 1;

	NewMaterial->Expressions.Add(AddMult_One);

	NewMaterial->WorldPositionOffset.Expression = AddMult_One;

	UMaterialExpressionMultiply* MultSub_Sub = NewObject<UMaterialExpressionMultiply>(NewMaterial);

	MultSub_Sub->MaterialExpressionEditorX = -250;
	MultSub_Sub->MaterialExpressionEditorY = 650;

	NewMaterial->Expressions.Add(MultSub_Sub);

	AddMult_One->A.Expression = MultSub_Sub;

	UMaterialExpressionSubtract* SubtractOP_AWP = NewObject<UMaterialExpressionSubtract>(NewMaterial);

	SubtractOP_AWP->MaterialExpressionEditorX = -400;
	SubtractOP_AWP->MaterialExpressionEditorY = 650;

	NewMaterial->Expressions.Add(SubtractOP_AWP);

	UMaterialExpressionWorldPosition* AbsoluteWorldPosition = NewObject<UMaterialExpressionWorldPosition>(NewMaterial);

	AbsoluteWorldPosition->MaterialExpressionEditorX = -650;
	AbsoluteWorldPosition->MaterialExpressionEditorY = 650;

	NewMaterial->Expressions.Add(AbsoluteWorldPosition);

	UClass* ObjectPositionClass = FindObject<UClass>(ANY_PACKAGE, *FString("/Script/Engine.MaterialExpressionObjectPositionWS"));
	UMaterialExpression* ObjectPosition = NewObject<UMaterialExpression>(NewMaterial, ObjectPositionClass,
																		FName("UMaterialExpressionObjectPositionWS"));

	ObjectPosition->MaterialExpressionEditorX = -650;
	ObjectPosition->MaterialExpressionEditorY = 800;

	NewMaterial->Expressions.Add(ObjectPosition);

	SubtractOP_AWP->A.Expression = AbsoluteWorldPosition;
	SubtractOP_AWP->B.Expression = ObjectPosition;


	UMaterialExpressionSubtract* SubtractDiv_One = NewObject<UMaterialExpressionSubtract>(NewMaterial);

	SubtractDiv_One->MaterialExpressionEditorX = -400;
	SubtractDiv_One->MaterialExpressionEditorY = 800;

	SubtractDiv_One->ConstB = 1;

	NewMaterial->Expressions.Add(SubtractDiv_One);

	MultSub_Sub->A.Expression = SubtractOP_AWP;
	MultSub_Sub->B.Expression = SubtractDiv_One;


	UMaterialExpressionDivide* DivideAdd_Two = NewObject<UMaterialExpressionDivide>(NewMaterial);

	DivideAdd_Two->MaterialExpressionEditorX = -550;
	DivideAdd_Two->MaterialExpressionEditorY = 900;

	DivideAdd_Two->ConstB = 2;

	NewMaterial->Expressions.Add(DivideAdd_Two);

	SubtractDiv_One->A.Expression = DivideAdd_Two;

	UMaterialExpressionAdd* AddSine_One = NewObject<UMaterialExpressionAdd>(NewMaterial);

	AddSine_One->MaterialExpressionEditorX = -700;
	AddSine_One->MaterialExpressionEditorY = 900;

	AddSine_One->ConstB = 1;

	NewMaterial->Expressions.Add(AddSine_One);

	DivideAdd_Two->A.Expression = AddSine_One;

	UMaterialExpressionSine* Sine = NewObject<UMaterialExpressionSine>(NewMaterial);

	Sine->MaterialExpressionEditorX = -850;
	Sine->MaterialExpressionEditorY = 900;

	NewMaterial->Expressions.Add(Sine);

	AddSine_One->A.Expression = Sine;

	UMaterialExpressionMultiply* MultTime_Speed = NewObject<UMaterialExpressionMultiply>(NewMaterial);

	MultTime_Speed->MaterialExpressionEditorX = -1000;
	MultTime_Speed->MaterialExpressionEditorY = 900;

	NewMaterial->Expressions.Add(MultTime_Speed);

	Sine->Input.Expression = MultTime_Speed;

	UMaterialExpressionTime* Time = NewObject<UMaterialExpressionTime>(NewMaterial);
	Time->MaterialExpressionEditorX = -1150;
	Time->MaterialExpressionEditorY = 900;

	NewMaterial->Expressions.Add(Time);

	UMaterialExpressionScalarParameter* PulseSpeed = NewObject<UMaterialExpressionScalarParameter>(NewMaterial);
	PulseSpeed->ParameterName = TEXT("PulseSpeed");

	PulseSpeed->DefaultValue = InSpeed;

	PulseSpeed->MaterialExpressionEditorX = -1150;
	PulseSpeed->MaterialExpressionEditorY = 1100;

	NewMaterial->Expressions.Add(PulseSpeed);

	MultTime_Speed->A.Expression = Time;
	MultTime_Speed->B.Expression = PulseSpeed;
}

FLinearColor FMyPluginModule::ParseColor(FString& Value)
{
	TArray<FString> RGBArr;
	TArray<uint8> RGBAByteArr;
	RGBArr.SetNumZeroed(4);
	RGBAByteArr.SetNumZeroed(4);

	int32 FormatCounter = 0;
	for (TCHAR Char : Value)
	{
		if (Char == ' ')
		{
			FormatCounter++;
		}
	}

	for (size_t Index = 0; Index < FormatCounter + 1; Index++)
	{
		int32 Val = 0;
		if ((Value.Split((" "), &RGBArr[Index], &Value)))
		{
			Val = FCString::Atoi(*RGBArr[Index]);
			RGBAByteArr[Index] = (uint8)Val;

		}
		else if (Value.Len() > 0)
		{
			RGBArr[Index] = Value;
			Val = FCString::Atoi(*RGBArr[Index]);
			RGBAByteArr[Index] = (uint8)Val;
		}

	}

	if (FormatCounter < 3)
	{
		RGBAByteArr[3] = 255;
	}




	FColor Color = FColor(RGBAByteArr[0], RGBAByteArr[1], RGBAByteArr[2], RGBAByteArr[3]);
	FLinearColor LinearColor = Color.ReinterpretAsLinear();
	return LinearColor;
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyPluginModule, MyPlugin)