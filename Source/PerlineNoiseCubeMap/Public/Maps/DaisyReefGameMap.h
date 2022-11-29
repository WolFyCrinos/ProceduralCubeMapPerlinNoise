// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/DaisyReefMapElement.h"
#include "GameFramework/Actor.h"
#include "DaisyReefGameMap.generated.h"

class UDaisyReefMapObject;

UCLASS(Blueprintable, BlueprintType)
class PERLINENOISECUBEMAP_API ADaisyReefGameMap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADaisyReefGameMap();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|MapObjectClass")
	TArray<ADaisyReefMapElement*> PerlinNoiseMap = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|MapObjectClass")
	TSubclassOf<UDaisyReefMapObject> MapObjectClass = nullptr;

private:
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="DaisyReef|PerlinNoiseMap")
	virtual TArray<ADaisyReefMapElement*> GenerateMap(const int MapWidthX, const int MapWidthY, const int Height,
	                                                  const float Scale);
};
