#pragma once
#include "../../../../Components/Component.h"
#include "../Gameplay/RegenStat.h"



// The info gathered when an object is damaged.
struct SDamageInfo
{
	// Determines if the attack killed the target.
	bool Killed{ false };

	// The amount of leftover damage after the target died.
	float OverkillDamage;

	// The amount of damage this object took.
	float DamageDealt;

	// The amount of health this object has remaining.
	float RemainingHealth;
};



// The information gathered when an object is healed.
struct SHealInfo
{
	// The amount of healing the target actually healed for.
	float HealAmount;

	// The health value the target healed to.
	float HealedTo;

	// The amount of health healed over the maximum.
	float OverHeal;
};



// A component type that gives objects health and has helper functions for damaging.
class CHealthComponent : public CComponent
{
private:
	/// Properties

	// The timer used to handle immunity frames.
	STimer* ImmunityTimer{ nullptr };

protected:
	// Should this object be allowed to take damage.
	bool Immune{ false };

	// Should this object have immunity frames.
	bool AllowImmunityFrames{ true };

	// Determines how long this object has immunity frames for.
	float ImmunityDuration{ 0.5f };

	// Should this object take a fixed amount of damage when hit.
	bool UseFixedDamage{ false };

	// The amount of damage this object will take when hit (only used if UseFixedDamage = true).
	float FixedDamage{ 1.0f };

public:
	// Represents if this object is alive.
	bool Dead{ false };

	// This object's health.
	SRegenStat Health;


public:
	/// Constructors

	// Constructor, Default.
	CHealthComponent(SComponentInfo Info);

	// Destructor.
	~CHealthComponent();



	/// Overridables
	
	// Runs when this component is created.
	virtual void Begin() override;

	// Runs when this component is destroyed.
	virtual void End() override;

	// Updates every frame.
	virtual void Update() override;

	

	/// Functions

private:
	// The timer bound function. Called when the timer ends.
	void ImmunityEnd(ETimerMethod Method);

protected:
	
	// Called when this object gets hurt.
	virtual void OnHurt() {}

	// Called when this object is killed.
	virtual void OnDeath() {}

	// Called when this object is healed.
	virtual void OnHeal() {}

	// Called when thsi object is revived.
	virtual void OnRevived() {}

public:
	// Calculates the amount of damage thsi object should take.
	// @param RawDamage - The initial damage.
	// @return - The recalculated damage.
	virtual float CalculateDamage(const float RawDamage) const;

	// Damages this object by an inputted amount.
	// @param Damage - The amount of damage this object should take.
	// @param IgnoreImmunity - Should the damage bypass the immunity frames.
	// @return - Qurry results from the damage.
	virtual SDamageInfo ApplyDamage(float Damage, bool IgnoreImmunity = false);

	// Heals this object by an inputted amount.
	// @param Amount - The amount of healing this object should recieve.
	// @param Revive - Determines if this heal can revive the target.
	// @return - Qurry results from the heal.
	virtual SHealInfo ApplyHeal(float Amount, bool Revive = false);
};