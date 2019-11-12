#pragma once
#include "../Character.h"


class CTestMove :public CCharacter
{
private:
	class CStaticMeshComponent* Mesh;
	class CSphereComponent* SphereCollider;

public:
	bool AllowMovement{ true };

public:
	CTestMove(SObjectBase Base);


	virtual void SetupInput(CInputManager* Input) override;


	void TMoveForward(float Value);

	void TMoveSideways(float Value);
};