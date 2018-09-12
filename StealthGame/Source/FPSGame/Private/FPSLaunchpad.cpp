// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchpad.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"



// Sets default values
AFPSLaunchpad::AFPSLaunchpad()
{
	//TODO: figure out how to apply a material to a static mesh here
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
}

// Called when the game starts or when spawned
void AFPSLaunchpad::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSLaunchpad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped with launch pad!"));

}

