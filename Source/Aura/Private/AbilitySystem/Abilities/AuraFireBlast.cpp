// Jakub Rak


#include "AbilitySystem/Abilities/AuraFireBlast.h"


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
		"</><Damage>%d</><Default> fire damage with chance to burn</>\n\n"),NumFireBalls, ManaCost, Cooldown, Level, ScaledDamage);
}

FString UAuraFireBlast::GetNextLevel(int32 Level)
{

	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return GetDescription(Level);
}
