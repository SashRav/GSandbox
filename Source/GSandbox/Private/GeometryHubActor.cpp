// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)


// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();

	//DoActorSpawn1();
	//DoActorSpawn2();
	//DoActorSpawn3();
	DoActorSpawn4();
	
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogGeometryHub, Warning, TEXT("property pointer %i, is valid %i"), PropertyActor != nullptr, IsValid(PropertyActor));
	UE_LOG(LogGeometryHub, Error, TEXT("None property pointer %i, is valid %i"), NonePropertyActor != nullptr, IsValid(NonePropertyActor));

}

void AGeometryHubActor::DoActorSpawn1()
{
	UWorld* World = GetWorld();
	if (World) {
		for (int32 i = 0; i < 10; i++) {
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 300.0f));
			ABaseGeometryActor* Geometry = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);

			if (Geometry) {
				FGeometryData Data;
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				Geometry->SetGeometryData(Data);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn2()
{
	UWorld* World = GetWorld();
	if (World) {
		for (int32 i = 0; i < 10; i++) {
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 700.0f));
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);

			if (Geometry) {
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				Geometry->SetGeometryData(Data);
				Geometry->FinishSpawning(GeometryTransform);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn3()
{
	UWorld* World = GetWorld();
	if (World) {
		for (const FGeometryPayload Payload : GeometryPayloads) {
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform);
			if (Geometry) {
				Geometry->SetGeometryData(Payload.Data);
				Geometry->OnColorChanged.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
				Geometry->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);
				Geometry->FinishSpawning(Payload.InitialTransform);
			}
		}
	}
}


void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogGeometryHub, Warning, TEXT("Actor name: %s Color %s"), *Name, *Color.ToString());
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if (!Actor) return;
	UE_LOG(LogGeometryHub, Error, TEXT("Timer finished: %s"), *Actor->GetName());

	ABaseGeometryActor* Geometry = Cast<ABaseGeometryActor>(Actor);
	if (!Geometry) return;

	UE_LOG(LogGeometryHub, Display, TEXT("Cast is success, amplitude %s"), *CollectAllData(Geometry));

	Geometry->Destroy();
	//Geometry->SetLifeSpan(2.0f);
}

FString AGeometryHubActor::CollectAllData(AActor* Actor)
{
	ABaseGeometryActor* Geometry = Cast<ABaseGeometryActor>(Actor);
	if (!Geometry) return "No Class exists";
	float Amplitude = Geometry->GetGeometryData().Amplitude;
	float Frequency = Geometry->GetGeometryData().Frequency;
	EMovementType MoveType = Geometry->GetGeometryData().MoveType;
	FLinearColor Color = Geometry->GetGeometryData().Color;
	float TimerRate = Geometry->GetGeometryData().TimerRate;

	
	//FString AllData = FString::Printf(TEXT(" \n == ALL Stat == \n %.2f \n %.2f \n %s \n %s \n %.2f"), Amplitude, Frequency, MoveType, Color.ToString(), TimerRate);
	FString AllData = FString::Printf(TEXT(" \n == ALL Stat == \n %.2f \n %.2f \n %.2f \n %s "), Amplitude, Frequency, TimerRate, *Color.ToString());

	return FString(AllData);
}



void AGeometryHubActor::DoActorSpawn4()
{
	if (!GetWorld()) return;

	FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(700.0f, 300.0f, 700.0f));
	NonePropertyActor = GetWorld()->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);

	GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(700.0f, 700.0f, 700.0f));
	PropertyActor = GetWorld()->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);
}
