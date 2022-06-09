// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "CustomCommandlet.generated.h"

/**
 * 
 */
UCLASS()
class MYPLUGIN_API UCustomCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	int32 Main(const FString& Params);
	
};
