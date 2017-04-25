// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
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

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(Body);

	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));
	Cam->SetupAttachment(SpringArm);

	Body->SetCapsuleHalfHeight(90.0f);
	Body->SetCapsuleRadius(36.0f);

	Mesh->SetupAttachment(Body);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Mesh(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Robo.SK_CharM_Robo'"));
	Mesh->SetSkeletalMesh(SK_Mesh.Object);
	Mesh->SetRelativeLocationAndRotation (FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));

	//Cam->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-20.0f, 0.0f, 0.0f));

	SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 650.0f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	MaxHP = 100.0f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}


// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHP = MaxHP;

	int32 NewIndex = FMath::RandRange(0, CharacterAssets.Num() - 1);
	UABGameInstance* ABGameInstance = Cast<UABGameInstance>(GetGameInstance());
	if (ABGameInstance)
	{
		TAssetPtr<USkeletalMesh> NewCharacter = Cast<USkeletalMesh>(ABGameInstance->AssetLoader.SynchronousLoad(CharacterAssets[NewIndex]));
		if (NewCharacter)
		{
			Mesh->SetSkeletalMesh(NewCharacter.Get());
		}
	}
	AB_LOG(Warning, TEXT("BeginPlay Call"));
}

// Called every frame
void AABPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector InputVector = FVector(CurrentUpDownVal, CurrentLeftRightVal, 0.0F); //x에는 위아래 y에는 양옆 
	if (InputVector.SizeSquared() > 0.0F)
	{
		FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX(InputVector);
		SetActorRotation(TargetRotation);
		AddMovementInput(GetActorForwardVector());
	}
}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);


	InputComponent->BindAxis("LeftRight", this, &AABPawn::LeftRightInput);
	InputComponent->BindAxis("UpDown", this, &AABPawn::UpDownInput);
}


void AABPawn::LeftRightInput(float NewInputVal)
{
	CurrentLeftRightVal = NewInputVal;
}

void AABPawn::UpDownInput(float NewInputVal)
{
	CurrentUpDownVal = NewInputVal;
}

