#include "Bullets/LaserRayBullet.h"
#include "Kismet/KismetSystemLibrary.h"

ALaserRayBullet::ALaserRayBullet()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALaserRayBullet::OnCollisionHappened()
{
	UKismetSystemLibrary::PrintString(this, HitResult.GetActor()->GetName());
	Destroy();
}