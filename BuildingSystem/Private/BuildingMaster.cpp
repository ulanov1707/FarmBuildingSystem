// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingMaster.h"

// Sets default values
ABuildingMaster::ABuildingMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
	SetReplicateMovement(true);

}

// Called when the game starts or when spawned
void ABuildingMaster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

