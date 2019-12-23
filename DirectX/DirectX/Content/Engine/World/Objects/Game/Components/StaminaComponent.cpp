#include "StaminaComponent.h"
#include "../../WorldObject.h"
#include "../../../../Components/CharacterComponent.h"


CStaminaComponent::CStaminaComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }
{
	Stamina.RegenType = ERegenType::Constant;
}


CStaminaComponent::~CStaminaComponent()
{
	CComponent::~CComponent();
}


void CStaminaComponent::Begin()
{
	Movement = GetOwner()->FindComponent<CCharacterComponent>();
	if (!Movement) printf("Error: Movement component not found CStaminaComponent.");
}


void CStaminaComponent::Update()
{
	Stamina.Update();

	if (Sprinting)
	{
		Stamina -= SprintCost * TTime::DeltaTime;
		if (Stamina <= 0.0f)
		{
			StopSprinting();
		}
	}
}


void CStaminaComponent::Sprint()
{
	if (Stamina > 0.0f && CanSprint)
	{
		Sprinting = true;
		Movement->SetMovementMode(EMovementType::Sprinting);
	}
}


void CStaminaComponent::StopSprinting()
{
	Sprinting = false;
	Movement->SetMovementMode(EMovementType::Running);
	Stamina.ResetDelay();
}


void CStaminaComponent::UseStamina(float Amount, bool DistruptRegen)
{
	Stamina = Amount;
	if (DistruptRegen)
	{
		Stamina.ResetDelay();
	}
}