#pragma once
#include "../../../../Components/Component.h"
#include "../Gameplay/RegenStat.h"



// A component used to give objects stamina.
class CStaminaComponent : public CComponent
{
private:
	/// Properties

	// Determines if this object is currently sprinting.
	bool Sprinting{ false };

	// A reference to the character movement component.
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

	// Starts sprinting.
	void Sprint();

	// Stops sprinting.
	void StopSprinting();

	// Consumes the stamina from this object by an inputted amount.
	void UseStamina(float Amount, bool DistruptRegen = false);
};