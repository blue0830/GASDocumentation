// Copyright 2020 Dan Kestranek.


#include "Custom/Abilities/GEBombCooldown.h"
#include "Characters/Abilities/AttributeSets/GDAttributeSetBase.h"

UGEBombCooldown::UGEBombCooldown() {

	/*FGameplayModifierInfo info;
	info.Attribute = FGameplayAttribute(FindFieldChecked<UProperty>(UGDAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(Cooldown)));*/
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(2));
	Period = 5;
}

