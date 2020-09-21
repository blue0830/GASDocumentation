// Copyright 2020 Dan Kestranek.


#include "Custom/Abilities/GEBombFire.h"
#include "Characters/Abilities/AttributeSets/GDAttributeSetBase.h"

UGEBombFire::UGEBombFire() {

	Period = 0.5;
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(10));

	FGameplayModifierInfo info;
	info.Attribute = FGameplayAttribute(FindFieldChecked<UProperty>(UGDAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UGDAttributeSetBase,Health)));
	info.ModifierOp = EGameplayModOp::Additive;
	info.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(-1));
	Modifiers.Add(info);

	FGameplayEffectCue effectCue;
	effectCue.GameplayCueTags.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayCue.Hero.Bomb.Fire")));
	GameplayCues.Add(effectCue);

	InheritableOwnedTagsContainer.CombinedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Fire")));
	InheritableOwnedTagsContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Fire")));

}
