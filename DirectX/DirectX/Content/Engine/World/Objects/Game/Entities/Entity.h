#pragma once
#include "../../Character.h"


class CEntity : public CCharacter
{
protected:
	/// Properties

	// 
	class CHealthComponent* Health;

	// 
	class CStaminaComponent* Stamina;


public:
	/// Constructors.

	// Constructor, Default.
	CEntity(SObjectBase Base);

	// Destructor.
	~CEntity();


	/// Functions


};