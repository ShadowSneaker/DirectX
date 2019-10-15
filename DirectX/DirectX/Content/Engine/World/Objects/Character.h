#pragma once
#include "Puppet.h"


// An object that can be controlled by the player/AI and has the
// fundamentals for a character object.
// This class contains the setup for charactre movement.
class CCharacter :public CPuppet
{
public:
	/// Properties

	//class CSkeletalMesh* Mesh;

	class CCharacterComponent* CharacterComponent;

	class CCapsuleComponent* CapsuleCollider;

public:
	/// Constructors

	// Constructor, Default.
	// @param Core - The core information to run this object.
	CCharacter(SObjectBase Core);

	// Destructor.
	~CCharacter();


	/// Functions

	virtual void Update() override;
};