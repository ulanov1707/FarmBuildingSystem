// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class SHOESTORESIMULATOR_API UBuildingSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetInteractHUD(bool Interact);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Server,reliable)
	void UpdateTraceServer();
	UFUNCTION(Server, reliable)
	void InteractServer(class ABuildingMaster * SpawnedBuildingActor);

	void InteractCrosshair();
	

private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMaterialInterface> ValidMaterial;

	//Dynamic Material - allow to change parameter values at runtime (color , etc )
	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> ValidMaterialDynamic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMaterialInterface> NotValidMaterial;

	//Dynamic Material - allow to change parameter values at runtime (color , etc )
	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> NotValidMaterialDynamic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FColor ValidColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FColor NotValidColor;
	
	TObjectPtr<class ABuildingMaster> MasterBuildingRef;

	UPROPERTY()
	FVector WorldLocation;
	UPROPERTY()
	FRotator WorldRotation;

	UPROPERTY()
	TObjectPtr<class UCameraComponent> TraceCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float TraceLengh = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ECollisionChannel> TraceChannel;

	UPROPERTY()
	TObjectPtr<class ABuildingMaster> SpawnedBuildingMaster;//just temp one 

	UPROPERTY()
	TArray<AActor*> AttachedActors;

	UPROPERTY()
	float Zoom = 0.f;

	UPROPERTY()
	TObjectPtr<class ABuildingMaster> InteractedBuildingRef;// persistent one

	UPROPERTY()
	FHitResult InteractionHitResult;

	UPROPERTY()
	bool bCanUpdateActorInfo = true; // bool for do once 
	UPROPERTY()
	bool bCanSetMateraial = true; // bool for Set Material
	UPROPERTY()
	bool bCanEndSnapStatus = true; // bool for Set Material'

	UPROPERTY()
	float RefRotation = 0.f;
	UPROPERTY()
	float RotationValue = 0.f;

	UFUNCTION(NetMulticast, Reliable)
	void ResetSetMaterial();

	void UpdateActorInformation();

	UFUNCTION(NetMulticast, Reliable)
	void UpdateActor(class ABuildingMaster * building);
	
};
