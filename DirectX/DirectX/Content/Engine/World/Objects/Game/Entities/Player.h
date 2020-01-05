#pragma once
#include "Entity.h"


// The class the player controlls.
class CPlayer : public CEntity
{
private:
	/// Properties



	/// Camera

	// The camera attached to the player.
	class CCameraComponent* Camera{ nullptr };

	// The reference to the score text.
	class CFont* ScoreText{ nullptr };

	// The speed this character rotates.
	float RotationSpeed{ 2.0f };

	// The score this player has.
	uint Score{ 0 };



public:
	/// Constructors

	// Constructor, Default.
	CPlayer(SObjectBase Base);

	// Destructor.
	~CPlayer();

	

	/// Overridables

	// Initializes the player input.
	virtual void SetupInput(CInputManager* Input) override;

	// Runs when the object is created.
	virtual void Begin() override;

	// Runs every frame.
	virtual void Update() override;



	/// Functions

	// Moves the player forward.
	void MoveForward(float Value);

	// Moves the player to the right.
	void MoveSideways(float Value);

	// Turns the player on the Y axis.
	void Turn(float Value);

	// Makes the player jump.
	void Jump(EInputMode InputMode);

	// Updates the score text on screen.
	void UpdateScore();

	// Adds points to this player.
	void AddPoints(uint Amount);



	/// Getters

	// Returns the attached camera.
	INLINE class CCameraComponent* GetCamera() const { return Camera; }
};