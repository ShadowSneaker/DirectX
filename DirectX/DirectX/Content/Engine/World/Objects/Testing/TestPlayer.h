#pragma once
#include "../Character.h"


class CTestPlayer :public CCharacter
{
private:
	/// Properties

	class CCameraComponent* Camera;
	float TempRotate{ 0.0f };
	float Speed{ 2.0f };

public:
	/// Constructors.
	CTestPlayer(SObjectBase Core);

	~CTestPlayer();


	/// Overridables

	// 
	virtual void SetupInput(CInputManager* Input) override;

	// 
	virtual void Update() override;


	/// Functions

	void MoveForward(float Axis);

	void MoveSideways(float Axis);

	void MoveUp(float Axis);

	void Turn(float Axis);
	void LookUp(float Axis);

	void CloseGame(EInputMode InputMode);

	void SpeedUp(EInputMode InputMode);

	inline class CCameraComponent* GetCamera() const { return Camera; }
};