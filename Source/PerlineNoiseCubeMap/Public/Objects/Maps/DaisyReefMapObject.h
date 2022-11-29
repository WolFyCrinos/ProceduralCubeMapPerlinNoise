// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DaisyReefMapObject.generated.h"

class ADaisyReefMapElement;

USTRUCT(BlueprintType)
struct FVector2DInt
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ForceUnits="units", ClampMin=0))
	int WidthX = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ForceUnits="units", ClampMin=0))
	int WidthY = 0;
};

USTRUCT(BlueprintType)
struct FMapProperties
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2DInt GridSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2DInt GridOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MapHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int SeaLevel;
};

USTRUCT(BlueprintType)
struct FMapNoiseProperties
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Seed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin=10))
	int Scale = 10;
};

USTRUCT(BlueprintType)
struct FMapElement
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D HeightLevelSpawnRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ShowTreeView))
	TSubclassOf<ADaisyReefMapElement> MapElement = nullptr;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PERLINENOISECUBEMAP_API UDaisyReefMapObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|MapProperties")
	FMapProperties MapProperties;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|MapNoiseProperties")
	FMapNoiseProperties MapNoiseProperties;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|MapElementsProperties")
	TSubclassOf<ADaisyReefMapElement> MapElementWater;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|MapElementsProperties")
	TArray<FMapElement> MapElements;
};
