#pragma once
#include "../WorldObject.h"



class CTestObject :public CWorldObject
{
	//class CCube* Cube;
	class CStaticMesh* Mesh;

	float TempRotate{ 0.0f };


public:
	CTestObject(SObjectBase Core);

	~CTestObject();


	virtual void Update() override;


	//inline class CCube* GetCube() const { return Cube; }
	inline class CStaticMesh* GetMesh() const { return Mesh; }
};