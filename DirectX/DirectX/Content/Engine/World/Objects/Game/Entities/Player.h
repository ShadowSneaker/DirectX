#pragma once
#include "Entity.h"


class CPlayer : public CEntity
{
private:
	/// Properties


	class CGun* Gun{ nullptr };

	class CCameraComponent* Camera{ nullptr };

	class CFont* ScoreText{ nullptr };


	uint Score{ 0 };


public:
	/// Constructors

	// Constructor, Default.
	CPlayer(SObjectBase Base);

	// Destructor.
	~CPlayer();

	

	/// Overridables

	virtual void SetupInput(CInputManager* Input) override;

	virtual void Begin() override;


	/// Functions

	void MoveForward(float Value);

	void MoveSideways(float Value);

	void MoveUp(float Value);

	void Turn(float Value);

	void Shoot(EInputMode InputMode);

	void UpdateScore();


	INLINE class CCameraComponent* GetCamera() const { return Camera; }
};