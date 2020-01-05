#pragma once
#include "../../Character.h"



// An object type used as a base for all characters and NPCs.
class CEntity : public CCharacter
{
protected:
	/// Properties

	// The health of this entity.
	class CHealthComponent* Health;

	// The stamina of this entity.
	class CStaminaComponent* Stamina;



public:
	/// Constructors.

	// Constructor, Default.
	CEntity(SObjectBase Base);

	// Destructor.
	~CEntity();


	/// Functions


};