#pragma once
#include "../../../../Math/MathValues.h"
#include "../../../../Core/Systems/Time.h"



// The types of regeneration there are.
enum class ERegenType
{
	Constant,		// Regenerates a set value per second.
	PercentMax,		// Regenerates a percentage of the max stat per second.
	PercentCurrent,	// Regenerates a percentage of the current stat per second.
	Missing			// Regenerates a percentage of the current missing stat per second.
};



// A helper struct to give regenerative stats to objects.
struct SRegenStat
{
private:
	/// Properties

	// Represents if this statis currently regenerating.
	bool Regenerating{ false };

	// The timer that triggers the regeneration.
	float RegenTimer;

public:
	// Should this stat be allowed to be consumed.
	bool AllowConsumption{ true };

	// The current value of this stat.
	float Value{ 100.0 };

	// The maximum amount of this stat.
	float MaxValue{ 100.0f };

	// Allows this object to regenerate mana.
	bool AllowRegen{ true };

	// The delay before mana starts regenerating.
	float RegenDelay{ 2.0f };

	// The method how this object should regenerate.
	ERegenType RegenType{ ERegenType::Constant };

	// The rate this object regenerates (per second).
	float RegenAmount{ 5.0f };


	/// Operators

	// Removes the main stat from this stat by a float amount.
	INLINE SRegenStat operator-=(float F);

	// Adds the main stat from this stat by a float amount.
	INLINE SRegenStat operator+=(float F);

	// Sets the current amount of stat this stat has.
	INLINE SRegenStat operator=(float F);

	// Returns the current stat value.
	INLINE operator float() const;



	/// Functions

	// Handle's this stat's regeneration.
	INLINE void Update();
	

	// Consumes this stat (if AllowConsumption is enabled).
	// @param Amount - The amount this value will be consumed.
	INLINE void UseStat(float Amount);
	
	// Resets the delay on this stat.
	INLINE void ResetDelay();



	/// Getters

	// Returns if this object is currently regenerating.
	INLINE bool IsRegenerating() const { return Regenerating; }
};



INLINE SRegenStat SRegenStat::operator-=(float F)
{
	UseStat(F);
	return *this;
}


INLINE SRegenStat SRegenStat::operator+=(float F)
{
	Value += F;
	if (Value > MaxValue) Value = MaxValue;
	return *this;
}


INLINE SRegenStat SRegenStat::operator=(float F)
{
	Value = TMath::Clamp(0.0f, MaxValue, F);
	return *this;
}


INLINE SRegenStat::operator float() const
{
	return Value;
}


void SRegenStat::Update()
{
	if (Regenerating)
	{
		switch (RegenType)
		{
		case ERegenType::Constant:
			Value += RegenAmount * TTime::DeltaTime;
			break;


		case ERegenType::PercentMax:
			Value += ((RegenAmount / 100.0f) * MaxValue) * TTime::DeltaTime;
			break;


		case ERegenType::PercentCurrent:
			if (Value == 0.0f) Value = 1.0f;
			Value += ((RegenAmount / 100.0f) * Value) * TTime::DeltaTime;
			break;


		case ERegenType::Missing:
			if (Value + 0.1f >= MaxValue) Value = MaxValue;
			Value += ((RegenAmount / 100.0f) * (MaxValue - Value)) * TTime::DeltaTime;
			break;
		}

		if (Value >= MaxValue)
		{
			Value = MaxValue;
			Regenerating = false;
		}
	}
	else
	{
		if (AllowRegen)
		{
			if (RegenTimer < RegenDelay)
			{
				RegenTimer += TTime::DeltaTime;
			}
			else
			{
				Regenerating = true;
			}
		}
	}
}


INLINE void SRegenStat::UseStat(float Amount)
{
	if (AllowConsumption)
	{
		Value -= Amount;
		if (Value < 0.0f) Value = 0.0f;

		if (AllowRegen)
		{
			RegenTimer = 0.0f;
			Regenerating = false;
		}
	}
}


INLINE void SRegenStat::ResetDelay()
{
	RegenTimer = 0.0f;
	Regenerating = false;
}