// Copyright 2020 Dan Kestranek.


#include "Custom/Abilities/GEBombDamage.h"
#include "Characters/Abilities/GDDamageExecCalculation.h"

UGEBombDamage::UGEBombDamage() {
	//Executions.Add()
	FGameplayEffectExecutionDefinition damageExecution;
	damageExecution.CalculationClass = UGDDamageExecCalculation::StaticClass();//TSubclassOf<UGDDamageExecCalculation>;
	Executions.Add(damageExecution);
}