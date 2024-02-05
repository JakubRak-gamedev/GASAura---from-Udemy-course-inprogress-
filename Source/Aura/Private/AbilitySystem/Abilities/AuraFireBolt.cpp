// Jakub Rak


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Interaction/CombatInterface.h"
#include "Aura/Public/AuraGameplayTags.h"


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
