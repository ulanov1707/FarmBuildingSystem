// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BuildingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UBuildingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SHOESTORESIMULATOR_API IBuildingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Building")
	void SetCrosshair(bool Crosshair);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Building")
	void SetInteract(bool Interact);
};
