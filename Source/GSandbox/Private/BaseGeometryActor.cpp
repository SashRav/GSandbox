// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeompetry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	printTypes();
	// printStringTypes();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABaseGeometryActor::printTypes()
{

	UE_LOG(LogBaseGeompetry, Warning, TEXT("Acotr name: %s"), *GetName());
	UE_LOG(LogBaseGeompetry, Warning, TEXT("Wearpons num: %d, kills num: %i"), WeaponsNum, killsNum);
	UE_LOG(LogBaseGeompetry, Warning, TEXT("Health: %f"), Health);
	UE_LOG(LogBaseGeompetry, Warning, TEXT("Is dead: %d"), isDead);
	UE_LOG(LogBaseGeompetry, Warning, TEXT("Has wearpon: %d"), static_cast<int>(hasWeapon));
}

void ABaseGeometryActor::printStringTypes() 
{
	FString Name = "John Connor";
	UE_LOG(LogBaseGeompetry, Display, TEXT("Name: %s"), *Name);

	FString WearponsNumStr = "Weapns num = " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is Dead = " + FString(isDead ? "true" : "false");

	FString Stat = FString::Printf(TEXT(" \n == ALL Stat == \n %s \n %s \n %s"), *WearponsNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogBaseGeompetry, Warning, TEXT("%s"), *Stat);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Stat, true, FVector2D(1.5f, 1.5f));

}