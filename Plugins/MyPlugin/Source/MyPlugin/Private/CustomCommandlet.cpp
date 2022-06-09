// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCommandlet.h"

int32 UCustomCommandlet::Main(const FString& Params)
{
	UE_LOG(LogTemp, Warning, TEXT("CustomCommandLet Parameters: %s"), *Params);

	return 0;
}