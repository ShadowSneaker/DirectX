#pragma once
#include "Puppet.h"



// An object that can be controlled by the player/AI and has the
// fundamentals for a character object.
// This class contains the setup for charactre movement.
class CCharacter :public CPuppet
{
public:
	/// Properties

	// The mesh of the character.
	class CStaticMeshComponent* Mesh;

	// The movement component of this character.
	class CCharacterComponent* CharacterComponent;

	// The collider around this character.
	class CBoxComponent* BoxCollider;



public:
	/// Constructors

	// Constructor, Default.
	// @param Core - The core information to run this object.
	CCharacter(SObjectBase Core);

	// Destructor.
	~CCharacter();



	/// Functions

	// Runs every frame.
	virtual void Update() override;
};