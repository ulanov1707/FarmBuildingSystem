// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSystem.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "BuildingMaster.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/HUD.h"
#include"BuildingInterface.h"


//#include "Materials/MaterialInterface.h"

// Sets default values for this component's properties
UBuildingSystem::UBuildingSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicated(true);

	TraceChannel = ECC_Visibility;
}


// Called when the game starts
void UBuildingSystem::BeginPlay()
{
	Super::BeginPlay();

	ValidMaterialDynamic= UMaterialInstanceDynamic::Create(ValidMaterial, this);
	ValidMaterialDynamic->SetVectorParameterValue(FName("Color"), ValidColor);

	NotValidMaterialDynamic= UMaterialInstanceDynamic::Create(NotValidMaterial, this);
	NotValidMaterialDynamic->SetVectorParameterValue(FName("Color"), NotValidColor);
	
	
}

//update crosshair
void UBuildingSystem::SetInteractHUD(bool Interact)
{
	AController* ControllerRef = (Cast<APawn>(GetOwner())->GetController());
	
	if(IsValid(ControllerRef))
	{	
		AHUD* HUDRef = Cast<APlayerController>(ControllerRef)->GetHUD();
		if (HUDRef && HUDRef->Implements<class UBuildingInterface>()) 
		{
			IBuildingInterface::Execute_SetInteract(HUDRef, Interact);
		}
	}
		
	
}


// Called every frame
void UBuildingSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateTraceServer();

	//if we are looking at buildable object
	if (IsValid(MasterBuildingRef))
		InteractServer(nullptr);
	else
		InteractCrosshair();


}

void UBuildingSystem::InteractCrosshair()
{
	FHitResult HitResult;
	FVector EndLocation = WorldRotation.Vector() * TraceLengh + WorldLocation;

	
	GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, EndLocation, TraceChannel, FCollisionQueryParams(), FCollisionResponseParams());

	if (HitResult.bBlockingHit == true) 
	{
		if (IsValid(Cast<ABuildingMaster>(HitResult.GetActor()))) 
		{
			SetInteractHUD(true);
			return;
		}
	}
	
	SetInteractHUD(false);
}



void UBuildingSystem::InteractServer_Implementation(class ABuildingMaster* SpawnedBuildingActor)
{
	SpawnedBuildingMaster = SpawnedBuildingActor;

	if (IsValid(SpawnedBuildingMaster)) 
	{
	// TODO
	}
	else 
	{
	
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActors(AttachedActors);
		FVector EndTrace = WorldRotation.Vector() * (TraceLengh * Zoom) + WorldLocation;

		GetWorld()->LineTraceSingleByChannel(InteractionHitResult, WorldLocation, EndTrace, TraceChannel, TraceParams);

		if (IsValid(InteractedBuildingRef)) 
		{
			//TODO	
		}
		else 
		{
			UpdateActorInformation();
		}
	}
}
void UBuildingSystem::ResetSetMaterial_Implementation()
{
	bCanSetMateraial = true;
}
void UBuildingSystem::UpdateActorInformation()
{
	AActor * UpdateeActor = IsValid(SpawnedBuildingMaster) ? SpawnedBuildingMaster :InteractionHitResult.GetActor() ;
	ABuildingMaster* BuildingRef = Cast<ABuildingMaster>(UpdateeActor);

	if (BuildingRef && bCanUpdateActorInfo == true) 
	{
		bCanUpdateActorInfo = false;
		ResetSetMaterial();
		UpdateActor(BuildingRef);

	}
	
	
}
void UBuildingSystem::UpdateActor_Implementation(ABuildingMaster* building)
{
	if (building == nullptr) 
	{
		bCanEndSnapStatus = true;//reseting snap status 

		if (IsValid(MasterBuildingRef)) 
		{
			RefRotation = RotationValue;
			MasterBuildingRef->SetActorEnableCollision(true);
		}
	}
	
}
void UBuildingSystem::UpdateTraceServer_Implementation()
{
	if (IsValid(MasterBuildingRef)) 
	{
		GetOwner()->GetActorEyesViewPoint(WorldLocation,WorldRotation);
	}
	else 
	{
		WorldRotation = Cast<APawn>(GetOwner())->GetController()->GetControlRotation();
		if(TraceCamera)
			WorldLocation = TraceCamera->GetComponentLocation();
	}
}

