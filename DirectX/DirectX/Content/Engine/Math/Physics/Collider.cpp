#include "Collider.h"
#include "../../Graphics/Meshes/StaticMesh.h"


CCollider::CCollider()
{

}


CCollider::CCollider(class CStaticMesh* Mesh)
{}


CCollider::CCollider(class CWorldObject* InOwner, STransform InTransform)
	:Transform{ InTransform }, Owner{ InOwner }
{

}


void CCollider::DrawDebug() const
{

}