// Jakub Rak


#include "AbilitySystem/Abilities/ArcaneShards.h"

FString UArcaneShards::GetDescription(int32 Level)
{

	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level > 1)
	{
		return FString::Printf(TEXT(
			"<Title>ARCANE SHARDS</>\n\n"
			"<Default>Level: %d</>\n"
			"<Default>ManaCost: </><ManaCost>%.1f</>\n"
			"<Default>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Spawns %d crystals empowered by arcane magic dealing: "
			"</><Damage>%d</><Default> arcane damage</>\n\n"), Level, ManaCost, Cooldown, FMath::Min(Level, MaxNumShards), ScaledDamage);
	}
	return FString::Printf(TEXT(
		"<Title>ARCANE SHARDS</>\n\n"
		"<Default>Level: %d</>\n"
		"<Default>ManaCost: </><ManaCost>%.1f</>\n"
		"<Default>Cooldown: </><Cooldown>%.1f</>\n\n"
		"<Default>Spawns crystal empowered by arcane magic dealing: "
		"</><Damage>%d</><Default> arcane damage</>\n\n"), Level, ManaCost, Cooldown, ScaledDamage);
}

FString UArcaneShards::GetNextLevel(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	return FString::Printf(TEXT(
		"<Title>ARCANE SHARDS</>\n\n"
		"<Default>Level: %d</>\n"
		"<Default>ManaCost: </><ManaCost>%.1f</>\n"
		"<Default>Cooldown: </><Cooldown>%.1f</>\n\n"
		"<Default>Spawns %d crystals empowered by arcane magic dealing: "
		"</><Damage>%d</><Default> arcane damage</>\n\n"), Level, ManaCost, Cooldown, FMath::Min(Level, MaxNumShards), ScaledDamage);
}
