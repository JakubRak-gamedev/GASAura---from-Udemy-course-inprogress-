// Jakub Rak


#include "AbilitySystem/Abilities/Electrocute.h"

FString UElectrocute::GetDescription(int32 Level)
{

	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level > 1)
	{
		return FString::Printf(TEXT(
			"<Title>ELECTROCUTE</>\n\n"
			"<Default>Level: %d</>\n"
			"<Default>ManaCost: </><ManaCost>%.1f</>\n"
			"<Default>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Emits %d beams of Lightning that deal: "
			"</><Damage>%d</><Default> lightning damage with chance to stun</>\n\n"), Level, ManaCost, Cooldown,Level, ScaledDamage);
	}
	return FString::Printf(TEXT(
		"<Title>ELECTROCUTE</>\n\n"
		"<Default>Level: %d</>\n"
		"<Default>ManaCost: </><ManaCost>%.1f</>\n"
		"<Default>Cooldown: </><Cooldown>%.1f</>\n\n"
		"<Default>Emits beam of lightning that deals, "
		"</><Damage>%d</><Default> lightning damage with chance to stun</>\n\n"), Level, ManaCost, Cooldown, ScaledDamage);
}

FString UElectrocute::GetNextLevel(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		"<Title>ELECTROCUTE</>\n\n"
		"<Default>Level: %d</>\n"
		"<Default>ManaCost: </><ManaCost>%.1f</>\n"
		"<Default>Cooldown: </><Cooldown>%.1f</>\n\n"
		"<Default>Emits %d beams of lightning that deals: "
		"</><Damage>%d</><Default> lightning damage with chance to stun</>\n\n"), Level, ManaCost, Cooldown, Level, ScaledDamage);
}

