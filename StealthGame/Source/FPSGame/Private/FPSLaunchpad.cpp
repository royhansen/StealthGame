// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchpad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FPSCharacter.h"



// Sets default values
AFPSLaunchpad::AFPSLaunchpad()
{
	//TODO: figure out how to apply a material to a static mesh here
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(75, 75, 50));
	RootComponent = OverlapComp;

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchpad::HandleOverlap);


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	LaunchStrength = 1500.0f;
	LaunchPitchAngle = 30.0f;


	/* 
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	RootComponent = OverlapComp;

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchpad::HandleOverlap);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(100.0f, 100.0f, 100.0f);
	DecalComp->SetupAttachment(RootComponent);
	*/
}

// Called when the game starts or when spawned
void AFPSLaunchpad::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSLaunchpad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchPitchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	
	ACharacter* MyPawn = Cast<ACharacter>(OtherActor);
	if (MyPawn) {
		MyPawn->LaunchCharacter(LaunchVelocity, true, true);
		UE_LOG(LogTemp, Warning, TEXT("Overlapped with launch pad!"));
	}
	
	else if (OtherComp && OtherComp->IsSimulatingPhysics()) {
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
		UE_LOG(LogTemp, Warning, TEXT("Box Overlapped with launch pad!"));
	}

	

}

