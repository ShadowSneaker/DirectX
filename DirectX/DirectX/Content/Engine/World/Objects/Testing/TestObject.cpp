#include "TestObject.h"
#include "../../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "../../../Graphics/Renderer.h"


CTestObject::CTestObject(SObjectBase Core)
	:CWorldObject::CWorldObject{ Core }
{
	//Cube = new CCube{ GetRenderer() };
	//Cube->SetShader("Shaders.hlsl");
	//Cube->Transform.SetParent(&Transform);
	//Cube->SetColour(1.0f, 1.0f, 1.0f, 1.0f);
	//GetRenderer()->AddMesh(Cube);

	//Mesh = new CStaticMesh{ GetRenderer() };
	//Mesh->SetMesh("Cube.obj");
	//Mesh->SetShader("Shaders.hlsl");
	//Mesh->Transform.SetParent(&Transform);
	//GetRenderer()->AddMesh(Mesh);

	Mesh = CreateComponent<CStaticMeshComponent>();
	Mesh->SetMesh("Cube.obj");
	Mesh->SetShader("Shaders.hlsl");
	Mesh->Transform.SetParent(&Transform);
}


CTestObject::~CTestObject()
{
	//GetRenderer()->DeleteMesh(Cube);
	CWorldObject::~CWorldObject();
}


void CTestObject::Update()
{
	TempRotate += 0.01f;
	Transform.Rotation = SQuaternion{ TO_RADIAN(TempRotate), TO_RADIAN(TempRotate / 2.0f), TO_RADIAN(TempRotate) };
}