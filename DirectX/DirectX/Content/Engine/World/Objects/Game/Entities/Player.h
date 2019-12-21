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

	void UpdateScore();


	INLINE class CCameraComponent* GetCamera() const { return Camera; }
};