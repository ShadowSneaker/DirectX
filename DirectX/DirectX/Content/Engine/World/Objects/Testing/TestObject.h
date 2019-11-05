#pragma once
#include "../WorldObject.h"



class CTestObject :public CWorldObject
{
	//class CCube* Cube;
	class CStaticMeshComponent* Mesh;

	float TempRotate{ 0.0f };


public:
	CTestObject(SObjectBase Core);

	virtual ~CTestObject() override;


	virtual void Update() override;


	//inline class CCube* GetCube() const { return Cube; }
	inline class CStaticMeshComponent* GetMesh() const { return Mesh; }
};