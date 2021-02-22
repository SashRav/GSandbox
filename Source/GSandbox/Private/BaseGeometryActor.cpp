// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeompetry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();

	// PrintTypes();
	// PrintStringTypes();
	// PrintTransform();
	
	SetColor(GeometryData.Color);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	HandleMovement();
}

void ABaseGeometryActor::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
	{
		FVector CurrentLocation = GetActorLocation();
		float Time = GetWorld()->GetTimeSeconds();
		CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);

		SetActorLocation(CurrentLocation);
	}
	break;
	case EMovementType::Static:
		break;

	default:
		break;
	}
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
{
	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial) {
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}


void ABaseGeometryActor::PrintTypes()
{

	UE_LOG(LogBaseGeompetry, Warning, TEXT("Acotr name: %s"), *GetName());
	UE_LOG(LogBaseGeompetry, Warning, TEXT("Wearpons num: %d, kills num: %i"), WeaponsNum, killsNum);
	UE_LOG(LogBaseGeompetry, Warning, TEXT("Health: %f"), Health);
	UE_LOG(LogBaseGeompetry, Warning, TEXT("Is dead: %d"), isDead);
	UE_LOG(LogBaseGeompetry, Warning, TEXT("Has wearpon: %d"), static_cast<int>(hasWeapon));
}

void ABaseGeometryActor::PrintStringTypes() 
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

void ABaseGeometryActor::PrintTransform() {

	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogBaseGeompetry, Warning, TEXT("Acotr name: %s"), *GetName());
	UE_LOG(LogBaseGeompetry, Warning, TEXT("Transform: %s"), *Transform.ToString());
	UE_LOG(LogBaseGeompetry, Warning, TEXT("Location: %s"), *Location.ToString());
	UE_LOG(LogBaseGeompetry, Warning, TEXT("Rotation: %s"), *Rotation.ToString());
	UE_LOG(LogBaseGeompetry, Warning, TEXT("Scale: %s"), *Scale.ToString());


	UE_LOG(LogBaseGeompetry, Error, TEXT("Human Transform: %s"), *Transform.ToHumanReadableString());
}


