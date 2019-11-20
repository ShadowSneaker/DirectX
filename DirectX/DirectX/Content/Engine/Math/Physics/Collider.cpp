#include "Collider.h"


CCollider::CCollider()
	:Overlap{ false }
{}


CCollider::CCollider(STransform InTransform)
	: Transform{ InTransform }, Overlap{ false }
{}


SVector CCollider::GetCenter() const
{
	SVector Max{ 0.0f };
	SVector Min{ 0.0f };
	for (uint i = 0; i < Vertices->size(); ++i)
	{
		if (Vertices)
		{
			Max = SVector::Max(Max, Vertices->at(i).Position);
			Min = SVector::Min(Min, Vertices->at(i).Position);
		}
	}

	return { Max.Lerp(Min, Max, 0.5f) };
}