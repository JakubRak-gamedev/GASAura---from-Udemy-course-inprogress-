// Jakub Rak


#include "AbilitySystem/Abilities/AuraFireBlast.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraFireBall.h"


FString UAuraFireBlast::GetDescription(int32 Level)
{
	
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
		return FString::Printf(TEXT(
		//Title
		"<Title>FIRE BLAST</>\n\n"

		//Level
		"<Default>Level: %d</>\n"

		//ManaCost
		"<Default>ManaCost: </><ManaCost>%.1f</>\n"

		//Cooldown
		"<Default>Cooldown: </><Cooldown>%.1f</>\n\n"

		//num fire balls
		"<Default>Launches %d</>"
		"<Default>Fire Balls in all directions, each comming back</>"
		"<Default>exploding upon return, causing </>"

		//damage type
		"</><Damage>%d</><Default> fire damage with chance to burn</>\n\n"),Level, ManaCost, Cooldown, NumFireBalls, ScaledDamage);
}

FString UAuraFireBlast::GetNextLevel(int32 Level)
{

	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		//Title
		"<Title>NEXT LEVEL</>\n\n"

		//Level
		"<Default>Level: %d</>\n"

		//ManaCost
		"<Default>ManaCost: </><ManaCost>%.1f</>\n"

		//Cooldown
		"<Default>Cooldown: </><Cooldown>%.1f</>\n\n"

		//num fire balls
		"<Default>Launches %d</>"
		"<Default>Fire Balls in all directions, each comming back</>"
		"<Default>exploding upon return, causing </>"

		//damage type
		"</><Damage>%d</><Default> fire damage with chance to burn</>\n\n"),Level, ManaCost, Cooldown, NumFireBalls, ScaledDamage);
}

TArray<AAuraFireBall*> UAuraFireBlast::SpawnFireBalls()
{
	TArray<AAuraFireBall*> FireBalls;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FRotator> Rotators = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumFireBalls);

	for(const FRotator& Rotator : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());
		
		AAuraFireBall* FireBall = GetWorld()->SpawnActorDeferred<AAuraFireBall>(
			FireBallClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			CurrentActorInfo->PlayerController->GetPawn(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);

		FireBall->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->ReturnToActor = GetAvatarActorFromActorInfo();

		FireBall->ExplosionDamageParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->SetOwner( GetAvatarActorFromActorInfo());
		
		FireBalls.Add(FireBall);
		
		FireBall->FinishSpawning(SpawnTransform);
	}
	
	return FireBalls;
}
