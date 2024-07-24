#include "Bullets/DestroyDecomposerBullet.h"
#include "Kismet/KismetSystemLibrary.h"

ADestroyDecomposerBullet::ADestroyDecomposerBullet()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADestroyDecomposerBullet::OnCollisionHappened()
{
	UKismetSystemLibrary::PrintString(this, HitResult.GetActor()->GetName());
	Destroy();
}