#include "CubeComponent.h"
#include "../../../Graphics/Renderer.h"


CCubeComponent::CCubeComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CCube::CCube{}
{
	GetRenderer()->AddMesh(this);
	SetTexture("NoTexture.png");
}


CCubeComponent::~CCubeComponent()
{
	GetRenderer()->RemoveMesh(this);
	CComponent::~CComponent();
	CCube::~CCube();
}


void CCubeComponent::SetShader(String FilePath, bool UseDefaultPath)
{
	Shader = GetRenderer()->SetShader(this, FilePath, UseDefaultPath);
}


void CCubeComponent::SetTexture(String FilePath, bool UseDefaultPath)
{
	Texture = GetRenderer()->SetTexture(FilePath, UseDefaultPath);
}