#include "StaticMeshComponent.h"
#include "../../../Graphics/Renderer.h"


CStaticMeshComponent::CStaticMeshComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CStaticMesh::CStaticMesh{}
{
	GetRenderer()->AddMesh(this);
}


CStaticMeshComponent::~CStaticMeshComponent()
{
	GetRenderer()->RemoveMesh(this);
	CComponent::~CComponent();
	CStaticMesh::~CStaticMesh();
}