#include "SkyBox.h"
#include "../../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "../../../Graphics/Renderer.h"


CTestSkyBox::CTestSkyBox(SObjectBase Base)
	:CWorldObject::CWorldObject{ Base }
{
	Mesh = CreateComponent<CStaticMeshComponent>();
	Mesh->SetMesh("Cube.obj");
	Mesh->SetShader("SkyBox.hlsl");
	Mesh->SetTexture("skybox02.dds");
	Mesh->InvertFaces = true;
	Mesh->Transform.SetParent(&Transform);
	Mesh->Transform.Scale = 1.0f;
	Mesh->SetColour(SColour::White());

	GetRenderer()->SkyBox = Mesh;
}


void CTestSkyBox::Update()
{
	CWorldObject::Update();

	if (Camera)
	{
		Mesh->Transform.Location = Camera->GetWorldLocation();
	}
}