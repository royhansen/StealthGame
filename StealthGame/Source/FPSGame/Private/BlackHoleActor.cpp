// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHoleActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABlackHoleActor::ABlackHoleActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlackHoleActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABlackHoleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<UPrimitiveComponent*> Boxes;
	SphereComp->GetOverlappingComponents(Boxes);
	for (UPrimitiveComponent* Box : Boxes) {
		if (Box && Box->IsSimulatingPhysics()) {
			Box->AddRadialForce(GetActorLocation(), 5000, -2000, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}

}

void ABlackHoleActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsRootComponentCollisionRegistered()) {
		OtherActor->Destroy();
	}

}

