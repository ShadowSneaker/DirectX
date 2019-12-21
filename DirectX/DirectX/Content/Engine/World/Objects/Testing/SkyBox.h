#pragma once
#include "../WorldObject.h"


class CTestSkyBox :public CWorldObject
{
private:
	/// Properties


	//class CStaticMeshComponent* Mesh;
	class CStaticMeshComponent* Mesh;

public:
	STransform* Camera;


public:
	CTestSkyBox(SObjectBase Base);



	virtual void Update() override;


	INLINE class CStaticMeshComponent* GetMesh() const { return Mesh; }
};