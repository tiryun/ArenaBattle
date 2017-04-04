// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABPawn.h"


// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	RootComponent = Body;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));

	Body->SetCapsuleHalfHeight(90.0f);
	Body->SetCapsuleRadius(36.0f);

	Mesh->SetupAttachment(Body);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Mesh(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Robo.SK_CharM_Robo'"));
	Mesh->SetSkeletalMesh(SK_Mesh.Object);
	Mesh->SetRelativeLocationAndRotation (FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));

	Cam->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-20.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

