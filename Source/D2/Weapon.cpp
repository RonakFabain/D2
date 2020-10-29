// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "D2Character.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
    FP_Gun->SetOnlyOwnerSee(true); // only the owning player will see this mesh
    FP_Gun->bCastDynamicShadow = false;
    FP_Gun->CastShadow = false;

    FP_Gun->SetupAttachment(RootComponent);

    FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
    FP_MuzzleLocation->SetupAttachment(FP_Gun);
    FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
    canShoot=true;
    // Default offset from the character location for projectiles to spawn
    GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
    Super::BeginPlay();

    TotalAmmo-=MagazineSize;
    currentAmmo=MagazineSize;
    
}

void AWeapon::Shoot(AActor* Player)
{
    

    if(TotalAmmo!=0 && currentAmmo!=0)
    {
        // canShoot=false;
       
        currentAmmo--;
       
        if(currentAmmo==0)
               Reload();
      
    
    
        auto Mesh = Cast<AD2Character>(Player)->Mesh1P;
        if (FireSound != NULL)
        {
            UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
        }

        // try and play a firing animation if specified
        if (FireAnimation != NULL)
        {
            // Get the animation object for the arms mesh
            UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
            if (AnimInstance != NULL)
            {
                AnimInstance->Montage_Play(FireAnimation, 1.f);
            }
        }

        if (MuzzleParticle)
        {
             UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleParticle,FP_MuzzleLocation->GetComponentTransform());
                                                
        }
    }
}

void AWeapon::SetUpAttachment(USkeletalMeshComponent* Mesh)
{
    FP_Gun->AttachToComponent(Mesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}


void AWeapon::Equip()
{
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);
    SetActorTickEnabled(true);
}

void AWeapon::Unequip()
{
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
}


void AWeapon::Reload()
{
    if(currentAmmo!=MagazineSize)
    {
        TotalAmmo-=(MagazineSize-currentAmmo);
        //20=-(6-1)=19

        if(TotalAmmo<=MagazineSize)
        {
            currentAmmo=MagazineSize;
            TotalAmmo=0;
        }
    }
   

   
    
    //10
    //4-0
    
    
   
   
    
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
