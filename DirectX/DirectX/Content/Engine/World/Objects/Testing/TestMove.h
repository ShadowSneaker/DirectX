#pragma once
#include "../Character.h"


class CTestMove :public CCharacter
{
private:
	class CStaticMeshComponent* Mesh;
	class CSphereComponent* SphereCollider;
	class CRigidbodyComponent* Rigid;

	float TempRotate{ 0.0f };
public:
	bool AllowMovement{ true };

public:
	CTestMove(SObjectBase Base);


	virtual void SetupInput(CInputManager* Input) override;

	virtual void Update() override;


	void TMoveForward(float Value);

	void TMoveSideways(float Value);
};