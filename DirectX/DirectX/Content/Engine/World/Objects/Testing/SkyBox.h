#pragma once
#include "../WorldObject.h"


class CTestSkyBox :public CWorldObject
{
private:
	/// Properties


	//class CStaticMeshComponent* Mesh;
	class CCubeComponent* Mesh;

public:
	STransform* Camera;


public:
	CTestSkyBox(SObjectBase Base);



	virtual void Update() override;
};