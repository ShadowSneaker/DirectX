#include "TestObject.h"
#include "../../../Graphics/Meshes/Primitives/Cube.h"
#include "../../../Graphics/Renderer.h"


CTestObject::CTestObject(SObjectBase Core)
	:CWorldObject::CWorldObject{ Core }
{
	Cube = new CCube{ GetRenderer() };
	Cube->SetShader("Shaders.hlsl");
	Cube->Transform.SetParent(&Transform);
	Cube->SetColour(1.0f, 1.0f, 1.0f, 1.0f);
	GetRenderer()->AddMesh(Cube);
}


CTestObject::~CTestObject()
{
	GetRenderer()->DeleteMesh(Cube);
}


void CTestObject::Update()
{
	TempRotate += 0.01f;

	Transform.Rotation = SQuaternion{ TO_RADIAN(TempRotate), TO_RADIAN(TempRotate / 2.0f), TO_RADIAN(TempRotate) };
}