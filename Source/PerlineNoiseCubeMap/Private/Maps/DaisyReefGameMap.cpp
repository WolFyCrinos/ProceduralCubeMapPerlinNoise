// Fill out your copyright notice in the Description page of Project Settings.

#include "Maps/DaisyReefGameMap.h"

#include "Actors/DaisyReefMapElement.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/Maps/DaisyReefMapObject.h"

// Sets default values
ADaisyReefGameMap::ADaisyReefGameMap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADaisyReefGameMap::BeginPlay()
{
	Super::BeginPlay();

	PerlinNoiseMap.Empty();

	PerlinNoiseMap = GenerateMap(MapObjectClass.GetDefaultObject()->MapProperties.GridSize.WidthX,
	                             MapObjectClass.GetDefaultObject()->MapProperties.GridSize.WidthY,
	                             MapObjectClass.GetDefaultObject()->MapProperties.MapHeight,
	                             MapObjectClass.GetDefaultObject()->MapNoiseProperties.Scale);
}

TArray<ADaisyReefMapElement*> ADaisyReefGameMap::GenerateMap(const int MapWidthX, const int MapWidthY, const int Height,
                                                             const float Scale)
{
	TArray<ADaisyReefMapElement*> NewPerlinNoiseMap = {};
	
	for (int y = 0; y < MapWidthY; ++y)
	{
		for (int x = 0; x < MapWidthX; ++x)
		{
			for (int z = 0; z < Height; ++z)
			{
				float SampleX = x / Scale;
				float SampleY = y / Scale;

				float PerlinValue = FMath::PerlinNoise2D(FVector2D(SampleX, SampleY));

				for (const auto [HeightLevelSpawnRange, MapElement] : MapObjectClass.GetDefaultObject()->MapElements)
				{
					if (z >= HeightLevelSpawnRange.X && z < HeightLevelSpawnRange.Y)
					{
						FActorSpawnParameters SpawnInfo;
						SpawnInfo.Instigator = GetInstigator();
						SpawnInfo.ObjectFlags |= RF_Transient; // We never want to save player controllers into a map
						SpawnInfo.bDeferConstruction = true;

						FVector NewElementLocation = FVector(
							x * MapObjectClass.GetDefaultObject()->MapProperties.GridOffset.WidthX,
							y * MapObjectClass.GetDefaultObject()->MapProperties.GridOffset.WidthY,
							z * 100);

						if (z <= FMath::RoundToInt(FMath::GetMappedRangeValueClamped(FVector2D(-1, 1), FVector2D(0, Height), PerlinValue)))
						{
							ADaisyReefMapElement* NewMapElement = GetWorld()->SpawnActor<ADaisyReefMapElement>(
							MapElement, NewElementLocation, FRotator::ZeroRotator, SpawnInfo);

							if (NewMapElement)
							{
								UGameplayStatics::FinishSpawningActor(NewMapElement,
																	  FTransform(
																		  FRotator::ZeroRotator, NewElementLocation));
								NewPerlinNoiseMap.Add(NewMapElement);
							}
						}
						else if (z <= MapObjectClass.GetDefaultObject()->MapProperties.SeaLevel && z > FMath::RoundToInt(FMath::GetMappedRangeValueClamped(FVector2D(-1, 1), FVector2D(0, Height), PerlinValue)))
						{
							ADaisyReefMapElement* NewMapElement = GetWorld()->SpawnActor<ADaisyReefMapElement>(
							MapObjectClass.GetDefaultObject()->MapElementWater, NewElementLocation, FRotator::ZeroRotator, SpawnInfo);

							if (NewMapElement)
							{
								UGameplayStatics::FinishSpawningActor(NewMapElement,
																	  FTransform(
																		  FRotator::ZeroRotator, NewElementLocation));
								NewPerlinNoiseMap.Add(NewMapElement);
							}
						}
					}
				}
			}
		}
	}

	return NewPerlinNoiseMap;
}
