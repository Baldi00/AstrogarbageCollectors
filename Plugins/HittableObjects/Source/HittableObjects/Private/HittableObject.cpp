#include "HittableObject.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"

AHittableObject::AHittableObject()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    NetCullDistanceSquared = 150000 * 150000;
}

void AHittableObject::BeginPlay()
{
    Super::BeginPlay();
    if (HasAuthority())
    {
        Velocity = UKismetMathLibrary::RandomUnitVector() * UKismetMathLibrary::RandomFloatInRange(50, 200);
        AngularVelocity = FRotator(UKismetMathLibrary::RandomFloatInRange(-20, 20),
            UKismetMathLibrary::RandomFloatInRange(-20, 20), UKismetMathLibrary::RandomFloatInRange(-20, 20));
    }
}

void AHittableObject::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CurrentLocation = GetActorLocation();
    CurrentRotation = GetActorRotation();

    AddActorWorldOffset(Velocity * DeltaTime);

    if (HasAuthority())
        AddActorWorldRotation(AngularVelocity * DeltaTime);
}

void AHittableObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION(AHittableObject, Velocity, COND_InitialOnly);
    DOREPLIFETIME_CONDITION(AHittableObject, AngularVelocity, COND_InitialOnly);
    DOREPLIFETIME_CONDITION_NOTIFY(AHittableObject, CurrentLocation, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(AHittableObject, CurrentRotation, COND_None, REPNOTIFY_OnChanged);
}

void AHittableObject::OnRep_CurrentLocation()
{
    if (!HasAuthority() && FVector::DistSquared(CurrentLocation, GetActorLocation()) > 1000)
        SetActorLocation(CurrentLocation);
}

void AHittableObject::OnRep_CurrentRotation()
{
    SetActorRotation(FMath::RInterpTo(GetActorRotation(), CurrentRotation, 1/60.f, 1.f));
}

