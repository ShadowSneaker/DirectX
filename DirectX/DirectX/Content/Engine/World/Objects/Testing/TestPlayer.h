#pragma once
#include "../Character.h"


class CTestPlayer :public CCharacter
{
private:
	/// Properties

	class CCamera* Camera;

public:
	/// Constructors.
	CTestPlayer(SObjectBase Core);

	~CTestPlayer();


	/// Functions

	virtual void SetupInput(CInputManager* Input) override;


	void MoveForward(float Axis);

	void MoveSideways(float Axis);

	void MoveUp(float Axis);
};