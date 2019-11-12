#pragma once
#include "../Character.h"


class CTestPlayer :public CCharacter
{
private:
	/// Properties

	class CCameraComponent* Camera;
	float TempRotate{ 0.0f };
	float Speed{ 500.0f };

public:
	/// Constructors.
	CTestPlayer(SObjectBase Core);

	~CTestPlayer();


	/// Functions

	virtual void SetupInput(CInputManager* Input) override;


	void MoveForward(float Axis);

	void MoveSideways(float Axis);

	void MoveUp(float Axis);

	void Turn(float Axis);
	void LookUp(float Axis);

	void CloseGame(EInputMode InputMode);

	void SpeedUp(EInputMode InputMode);

	inline class CCameraComponent* GetCamera() const { return Camera; }
};