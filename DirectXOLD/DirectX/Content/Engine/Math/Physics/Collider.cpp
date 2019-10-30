#include "Collider.h"


CCollider::CCollider()
{

}


CCollider::CCollider(class CWorldObject* InOwner, STransform InTransform)
	:Transform{ InTransform }, Owner{ InOwner }
{

}


void CCollider::DrawDebug() const
{

}