// Copyright 2020 Dan Kestranek.


#include "Custom/Abilities/GEBombCost.h"
#include "Characters/Abilities/AttributeSets/GDAttributeSetBase.h"

UGEBombCost::UGEBombCost() {
	//FGameplayEffectExecutionDefinition costExecution;
	//FGameplayEffectExecutionScopedModifierInfo modifierInfo;
	////modifierInfo.CapturedAttribute.AttributeToCapture.SetUProperty()FProperty
	//modifierInfo.
	//costExecution.CalculationModifiers.Add(modifierInfo);
	FGameplayModifierInfo info;
	info.Attribute = FGameplayAttribute(FindFieldChecked<UProperty>(UGDAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UGDAttributeSetBase, Mana)));
	info.ModifierOp = EGameplayModOp::Additive;
	info.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(-50));
	Modifiers.Add(info);
}