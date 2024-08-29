// Jakub Rak


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "GameFramework/ProjectileMovementComponent.h"


FString UAuraFireBolt::GetDescription(int32 Level)
{
	
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if(Level > 1)
	{
		return FString::Printf(TEXT(
		"<Title>FIRE BOLT</>\n\n"
		"<Default>Level: %d</>\n"
		"<Default>ManaCost: </><ManaCost>%.1f</>\n"
		"<Default>Cooldown: </><Cooldown>%.1f</>\n\n"
		"<Default>Launches %d bolts of fire, "
		"exploding on impact and dealing: "
		"</><Damage>%d</><Default> fire damage with chance to burn</>\n\n"),Level, ManaCost, Cooldown, Level, ScaledDamage);
	}
	return FString::Printf(TEXT(
	"<Title>FIRE BOLT</>\n\n"
	"<Default>Level: %d</>\n"
	"<Default>ManaCost: </><ManaCost>%.1f</>\n"
	"<Default>Cooldown: </><Cooldown>%.1f</>\n\n"
	"<Default>Launch a bolt of fire, "
	"exploding on impact and dealing: "
	"</><Damage>%d</><Default> fire damage with chance to burn</>\n\n") ,Level, ManaCost, Cooldown, ScaledDamage);
}

FString UAuraFireBolt::GetNextLevel(int32 Level)
{

	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
	"<Title>NEXT LEVEL</>\n\n"
	"<Default>Level: %d</>\n"
	"<Default>ManaCost: </><ManaCost>%.1f</>\n"
	"<Default>Cooldown: </><Cooldown>%.1f</>\n\n"
	"<Default>Launches %d bolts of fire, "	
	"exploding on impact and dealing: "
	"</><Damage>%d</><Default> fire damage with chance to burn</>\n\n"),Level,ManaCost,Cooldown,Level,ScaledDamage);
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		SocketTag);

	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	
	if(bOverridePitch) Rotation.Pitch = PitchOverride;
	
	const FVector Forward = Rotation.Vector();
	
	const int32 NumProjectiles =  FMath::Min(MaxNumOfProjectile, GetAbilityLevel());
	
	TArray<FRotator> Rotations = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);
	
	for(const FRotator& Rot : Rotations)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());
		
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

		
		if(HomingTarget != nullptr && HomingTarget->Implements<UCombatInterface>())
		{
			Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
		}
		else
		{
			Projectile->HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
			Projectile->HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
			Projectile->ProjectileMovement->HomingTargetComponent = Projectile->HomingTargetSceneComponent;
		}
		
		Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::FRandRange(HomingAccelerationMin, HomingAccelerationMax);
		Projectile->ProjectileMovement->bIsHomingProjectile = bLaunchHomingProjectiles;
			
		Projectile->FinishSpawning(SpawnTransform);
	}
	
}
