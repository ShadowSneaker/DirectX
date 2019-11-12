#include "SkyBox.h"
#include "../../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "../../../Components/Graphics/Meshes/CubeComponent.h"


CTestSkyBox::CTestSkyBox(SObjectBase Base)
	:CWorldObject::CWorldObject{ Base }
{
	Mesh = CreateComponent<CCubeComponent>();
	Mesh->SetShader("SkyBox.hlsl");
	Mesh->SetTexture("skybox02.dds");
	Mesh->InvertFaces = true;
	Mesh->Transform.SetParent(&Transform);
	Mesh->Transform.Scale = 3.0f;
	Mesh->SetColour(SColour::White());

}


void CTestSkyBox::Update()
{
	CWorldObject::Update();

	if (Camera)
	{
		Transform.Location = Camera->Location;
	}
}