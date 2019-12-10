#pragma once
#include "../../../../Components/Component.h"
#include "../Gameplay/RegenStat.h"


class CStaminaComponent : public CComponent
{
private:
	/// Properties

	bool Sprinting{ false };

	class CCharacterComponent* Movement{ nullptr };

public:

	// This object's stamina.
	SRegenStat Stamina;

	// Should this object be allowed to sprint.
	bool CanSprint{ true };

	// The amount of stamina sprinting consumes (per second).
	float SprintCost{ 1.0f };



public:
	/// Constructors

	// Constructor, Default.
	CStaminaComponent(SComponentInfo Info);

	// Destructor.
	~CStaminaComponent();


	/// Overridables

	// Runs when this component is created.
	virtual void Begin() override;

	// Updates every frame.
	virtual void Update() override;


	/// Functions

	void Sprint();

	void StopSprinting();

	// Consumes the stamina from this object by an inputted amount.
	void UseStamina(float Amount, bool DistruptRegen = false);
};