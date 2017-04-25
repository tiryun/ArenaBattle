// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "ABPawn.generated.h"

UCLASS(config = Game)
class ARENABATTLE_API AABPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AABPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Charactor")
	class UCapsuleComponent* Body;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Charactor")
	class USkeletalMeshComponent* Mesh;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Charactor")
	class UFloatingPawnMovement* Movement;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SpringArm")
	class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera") 
	class UCameraComponent* Cam;

	//디폴트 오브젝트에서만 에디트 EditDefaultsOnly 또는 인스턴스마다 따로 에디트 EditInstanceOnly 등의 설정이 있다
	UPROPERTY(config, BlueprintReadWrite, EditAnywhere, Category = "Stat")
		float MaxHP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stat")
		float CurrentHP;


public:
	UPROPERTY(config, BlueprintReadOnly, VisibleInstanceOnly, Category = "Asset")
		TArray<FStringAssetReference> CharacterAssets;


private:
	float CurrentLeftRightVal;
	float CurrentUpDownVal;

	UFUNCTION()
		void UpDownInput(float NewInputVal);

	UFUNCTION()
		void LeftRightInput(float NewInputval);

};
