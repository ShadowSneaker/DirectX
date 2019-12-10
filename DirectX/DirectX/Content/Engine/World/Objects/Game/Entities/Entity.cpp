#include "Entity.h"
#include "../Components/HealthComponent.h"
#include "../Components/StaminaComponent.h"


CEntity::CEntity(SObjectBase Base)
	:CCharacter::CCharacter{ Base }
{
	Health = CreateComponent<CHealthComponent>();
	Health->Health = 10.0f;
	Health->Health.MaxValue = 10.0f;

	Stamina = CreateComponent<CStaminaComponent>();
	Stamina->Stamina = 10.0f;
	Stamina->Stamina.MaxValue = 10.0f;

}


CEntity::~CEntity()
{

}