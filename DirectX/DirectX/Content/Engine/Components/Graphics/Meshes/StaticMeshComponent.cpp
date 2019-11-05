#include "StaticMeshComponent.h"
#include "../../../Graphics/Renderer.h"
#include "../../../World/Objects/WorldObject.h"


CStaticMeshComponent::CStaticMeshComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CStaticMesh::CStaticMesh{}
{
	GetRenderer()->AddMesh(this);
	SetTexture("NoTexture.png");
	Transform.SetParent(&GetOwner()->Transform);
}


CStaticMeshComponent::~CStaticMeshComponent()
{
	GetRenderer()->RemoveMesh(this);
	CComponent::~CComponent();
	//CStaticMesh::~CStaticMesh();
}


void CStaticMeshComponent::SetShader(String FilePath, bool UseDefaultPath)
{
	Shader = GetRenderer()->SetShader(this, FilePath, UseDefaultPath);
}


void CStaticMeshComponent::SetTexture(String FilePath, bool UseDefaultPath)
{
	Texture = GetRenderer()->SetTexture(FilePath, UseDefaultPath);
}