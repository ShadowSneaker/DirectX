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
	if (Vertices)
	{
		for (uint i = 0; i < Vertices->size(); ++i)
		{
			if (Vertices)
			{
				Max = SVector::Max(Max, Vertices->at(i).Position);
				Min = SVector::Min(Min, Vertices->at(i).Position);
			}
		}
	}
	return { Max.Lerp(Min, Max, 0.5f) };
}


void CCollider::Project(const SVector& Axis, const std::vector<SVector>& PTSet, float& MinAlong, float& MaxAlong) const
{
	//MinAlong = HUGE;
	//MaxAlong = HUGE;

	MinAlong = Axis.DotProduct(PTSet[0]);
	MaxAlong = MinAlong;
	for (uint i = 0; i < PTSet.size(); ++i)
	{
		//float DotValue{ PTSet[i].DotProduct(Axis) };
		float DotValue{ Axis.DotProduct(PTSet[i]) };
		if (DotValue < MinAlong) MinAlong = DotValue;
		if (DotValue > MaxAlong) MaxAlong = DotValue;
	}
}


bool CCollider::TestOverlaps(float Min1, float Max1, float Min2, float Max2) const
{
	return TMath::Range(Min1, Max1, Min2) || TMath::Range(Min2, Max2, Min1);
}


bool CCollider::CheckSATCollision(std::vector<SVector> Normals, const CCollider* Other) const
{
	for (uint i = 0; i < Normals.size(); ++i)
	{
		float Min1, Max1;
		float Min2, Max2;
		Project(Normals[i], GetVerticesLocations(), Min1, Max1);
		Project(Normals[i], Other->GetVerticesLocations(), Min2, Max2);
		if (!TestOverlaps(Min1, Max1, Min2, Max2)) return false;
	}
	return true;
}


bool CCollider::SATCollision(const CCollider* Other) const
{
	//if (Vertices->size() > 0 && Other->Vertices->size() > 0)
	//{
	if (!CheckSATCollision(GetNormals(), Other)) return false;
	if (!CheckSATCollision(Other->GetNormals(), this)) return false;
	//return true;
//}
	return true;
}


std::vector<SVector> CCollider::GetNormals() const
{
	std::vector<SVector> Result;
	Result.resize(Vertices->size());
	for (uint i = 0; i < Vertices->size(); ++i)
	{
		SVector A{ Vertices->at(i).Position };
		SVector B{ Vertices->at((i + 1 == Vertices->size()) ? 0 : i + 1).Position };
		SVector Edge{ A - B };
		Result[i] = SVector{ -Edge[X], Edge[Y], Edge[Z] };
		//Result[i] = Edge.Normalize();
	}
	return Result;
}


std::vector<SVector> CCollider::GetVerticesLocations() const
{
	std::vector<SVector> Result;
	SVector WorldLocation{ Transform.GetWorldLocation() };
	Result.resize(Vertices->size());
	for (uint i = 0; i < Vertices->size(); ++i)
	{
		Result[i] = Vertices->at(i).Position + WorldLocation;
	}
	return Result;
}