#pragma once
#include "Entity.h"


class CPlayer : public CEntity
{
private:
	/// Properties



	/// Camera

	class CCameraComponent* Camera{ nullptr };
	
	float CamLerpSpeed{ 25.0f };

	SVector2 CameraOffset;


	class CFont* ScoreText{ nullptr };

	float RotationSpeed{ 2.0f };

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

	virtual void Update() override;


	/// Functions

	void MoveForward(float Value);

	void MoveSideways(float Value);

	void Turn(float Value);

	void Jump(EInputMode InputMode);

	void UpdateScore();

	void AddPoints(uint Amount);


	INLINE class CCameraComponent* GetCamera() const { return Camera; }
};