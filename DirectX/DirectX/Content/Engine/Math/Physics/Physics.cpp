#include "Physics.h"
#include "../../World/Objects/WorldObject.h"


CPhysics::CPhysics()
{

}


CPhysics::~CPhysics()
{
	DeleteAllColliders();
}


void CPhysics::InitPhysics()
{

}


void CPhysics::Update()
{
	CurrentFrame = 0; // TODO: Change this to represent the performance counter.
	while (RunPhysics)
	{
		LastFrame = CurrentFrame;
		CurrentFrame = 0; // Change this to set the performance counter.
		DeltaTime = (float(CurrentFrame - LastFrame) / float(1 /*Change this to get the performance requency*/));
	
		// TODO: Do physics stuff.
	}
}


void CPhysics::DeleteAllColliders()
{
	while (!Colliders.empty())
	{
		delete Colliders.back().Collider;
		delete Colliders.back().RigidBody;
		Colliders.pop_back();
	}
}


void CPhysics::DeleteCollider(CCollider* Collider)
{
	if (Collider)
	{
		for (uint i = 0; i < Colliders.size(); ++i)
		{
			if (Colliders[i].Collider == Collider)
			{
				delete Colliders[i].RigidBody;
				Colliders.erase(Colliders.begin() + i);
				break;
			}
		}
		delete Collider;
	}
}


void CPhysics::RemoveCollider(CCollider* Collider)
{
	if (Collider)
	{
		for (uint i = 0; i < Colliders.size(); ++i)
		{
			if (Colliders[i].Collider == Collider)
			{
				Colliders.erase(Colliders.begin() + i);
			}
		}
	}
}


void CPhysics::AddCollider(CCollider* Collider)
{
	if (Collider)
	{
		Colliders.push_back(SColliderInfo{ Collider });
	}
}


void CPhysics::CreateCollider()
{

}


THitInfoList CPhysics::QuerryCollisions() const
{
	THitInfoList InfoList;
	for (uint i = 0; i < Colliders.size(); ++i)
	{
		for (uint j = 0; j < Colliders.size(); ++j)
		{
			if (i != j)
			{
				SHitInfo Info;

				if (Colliders[i].Collider->CheckCollision(Colliders[j].Collider))
				{
					Info.Hit = true;
					Info.HitObject = Colliders[i].Collider->Owner;
					InfoList.push_back(Info);
				}
			}
		}
	}
	return InfoList;
}


THitInfoList CPhysics::QuerryCollisions(CCollider* Collider, bool IgnoreSelf) const
{
	THitInfoList HitInfoList;

	for (uint i = 0; i < Colliders.size(); ++i)
	{
		if (Collider == Colliders[i].Collider && IgnoreSelf)
		{
			if (i + 1 < Colliders.size())
			{
				++i;
			}
			else
			{
				break;
			}

			// Do collision checks.
			if (Collider->CheckCollision(Colliders[i].Collider))
			{
				SHitInfo HitInfo{ true, Colliders[i].Collider };
				HitInfo.HitObject = Colliders[i].Collider->Owner;
				HitInfoList.push_back(HitInfo);

				SHitInfo OtherInfo{ true, Collider };
				OtherInfo.HitObject = Collider->Owner;

				Colliders[i].Collider->CallFunction(OtherInfo);
				Collider->CallFunction(HitInfo);
			}
		}
	}

	return HitInfoList;
}


SHitInfo CPhysics::Linecast(SVector Start, SVector End) const
{
	return SHitInfo();
}


SHitInfo CPhysics::Linecast(SVector Start, SVector End, TObjectList IgnoreObjects) const
{
	return SHitInfo();
}


SRaycastHit CPhysics::Raycast(SVector Start, SVector Direction, float Distance) const
{
	return SRaycastHit();
}


SRaycastHit CPhysics::Raycast(SVector Start, SVector Direction, float Distrance, TObjectList IgnoreObjects) const
{
	return SRaycastHit();
}


SRaycastHit CPhysics::Raycast(SVector Start, SVector Direction, float Distance, SRaycastHit& HitInfo) const
{
	return SRaycastHit();
}


SRaycastHit CPhysics::Raycast(SVector Start, SVector Direction, float Distrance, TObjectList IgnoreObjects, SRaycastHit& HitInfo) const
{
	return SRaycastHit();
}


THitInfoList CPhysics::LinecastMulti(SVector Start, SVector End) const
{
	return THitInfoList();
}


THitInfoList CPhysics::LinecastMulti(SVector Start, SVector End, TObjectList IgnoreObjects) const
{
	return THitInfoList();
}


std::vector<SRaycastHit> CPhysics::RaycastMulti(SVector Start, SVector Direction, float Distance) const
{
	return std::vector<SRaycastHit>();
}


std::vector<SRaycastHit> CPhysics::RaycastMulti(SVector Start, SVector Direction, float Distance, TObjectList IgnoreObjects) const
{
	return std::vector<SRaycastHit>();
}


std::vector<SRaycastHit> CPhysics::RaycastMulti(SVector Start, SVector Direction, float Distance, std::vector<SRaycastHit>& HitInfo) const
{
	return std::vector<SRaycastHit>();
}


std::vector<SRaycastHit> CPhysics::RaycastMulti(SVector Start, SVector Direction, float Distance, TObjectList IgnoreObjects, std::vector<SRaycastHit>& HitInfo) const
{
	return std::vector<SRaycastHit>();
}