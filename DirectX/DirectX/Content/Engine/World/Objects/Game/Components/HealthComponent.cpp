#include "HealthComponent.h"


CHealthComponent::CHealthComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }
{
	Health.RegenType = ERegenType::PercentCurrent;
	
}


CHealthComponent::~CHealthComponent()
{
	CComponent::~CComponent();
}


void CHealthComponent::Begin()
{
	ImmunityTimer = GetTimerManager()->AddTimer(GetOwner(), std::bind(&CHealthComponent::ImmunityEnd, this, std::placeholders::_1), ImmunityDuration, ETimerMethod::OnEnd, false, 0.0f, false, false);
}


void CHealthComponent::End()
{
	GetTimerManager()->DeleteTimer(ImmunityTimer);
}


void CHealthComponent::Update()
{
	if (!Dead)
	{
		Health.Update();
	}
}


void CHealthComponent::ImmunityEnd(ETimerMethod Method)
{
	Immune = false;
}


float CHealthComponent::CalculateDamage(const float RawDamage) const
{
	return RawDamage;
}


SDamageInfo CHealthComponent::ApplyDamage(float Damage, bool IgnoreImmunity)
{
	SDamageInfo Info;
	if (!Dead && Health.AllowConsumption && Damage > 0.0f)
	{
		if (!Immune || IgnoreImmunity)
		{
			if (UseFixedDamage) Damage = FixedDamage;
			else Damage = CalculateDamage(Damage);

			Info.OverkillDamage = Damage - Health.Value;

			Health -= Damage;
			Info.DamageDealt = Damage;
			Info.RemainingHealth = Health;

			if (AllowImmunityFrames)
			{
				GetTimerManager()->ResetTimer(ImmunityTimer);
				Immune = true;
			}

			OnHurt();

			if (Health <= 0.0f)
			{
				Dead = true;
				Info.Killed = true;

				OnDeath();
			}
		}
	}
	else
	{
		Info.DamageDealt = 0.0f;
		Info.OverkillDamage = 0.0f;
	}
	return Info;
}


SHealInfo CHealthComponent::ApplyHeal(float Amount, bool Revive)
{
	SHealInfo Info;
	if (Dead && Revive)
	{
		Dead = false;
		OnRevived();
	}

	if (!Dead)
	{
		Info.OverHeal = (Health + Amount) - Health.MaxValue;

		Health += Amount;
		Info.HealAmount = Amount;

		OnHeal();
	}
	else
	{
		Info.OverHeal = 0.0f;
	}

	Info.HealedTo = Health;
	return Info;
}