// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABWeapon.h"


// Sets default values
AABWeapon::AABWeapon() //프로젝트 실행 시 CDO 생성
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponHash")); //권장
	RootComponent = Weapon;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Weapon(TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Silly_Weapons/Blade_Balloon/SK_Blade_Balloon.SK_Blade_Balloon'"));
	Weapon->SetSkeletalMesh(SK_Weapon.Object);
}

// Called when the game starts or when spawned
void AABWeapon::BeginPlay() //런타임에 추가
{
	Super::BeginPlay();
	//Weapon = NewObject<USkeletalMeshComponent>(this); //비권장
}

// Called every frame
void AABWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

