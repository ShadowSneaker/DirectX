#include "Physics.h"
#include "Primitives/Line.h"


CPhysics::CPhysics()
{
	PhysicsThread = std::thread(&CPhysics::Update, this);
}


CPhysics::~CPhysics()
{
	DeleteAllBodies();
}


void CPhysics::DeleteAllBodies()
{
	Simulate = false;
	PhysicsThread.join();
	while (!Bodies.empty())
	{
		delete Bodies.back();
		Bodies.pop_back();
	}
}


void CPhysics::Update()
{
	PhysicsMutex.lock();
	while (Simulate)
	{
		// Calculate Delta Time.

		UpdateList();

		// TODO:
		// Put physics simulation here.
		if (Bodies.size() > 0)
		{
			uint Count = Bodies.size();
			for (uint i = 0; i < Count; ++i)
			{
				if (Bodies[i]->Rigidbody)
				{
					Bodies[i]->Collider->Transform.Location += (Bodies[i]->Rigidbody->Velocity + Gravity) * DeltaTime;
				}
			}
		}
	}
	PhysicsMutex.unlock();
}


void CPhysics::UpdateList()
{
	while (!RemoveQueue.empty())
	{
		RemoveFromSimulation(RemoveQueue.back());
		RemoveQueue.pop_back();
	}

	while (!InputQueue.empty())
	{
		AddToSimulation(InputQueue.back());
		InputQueue.pop_back();
	}
}


void CPhysics::AddToSimulation(SPhysicsBody* Body)
{
	for (uint i = 0; i < Bodies.size(); ++i)
	{
		if (Body == Bodies[i])
		{
			return;
		}
		Bodies.push_back(Body);
	}
}


void CPhysics::RemoveFromSimulation(SPhysicsBody* Body)
{
	for (uint i = 0; i < Bodies.size(); ++i)
	{
		if (Body == Bodies[i])
		{
			Bodies.erase(Bodies.begin() + i);
			return;
		}
	}
}


void CPhysics::AddPhysicsBody(SPhysicsBody* Body)
{
	if (Body)
	{
		for (uint i = 0; i < Bodies.size(); ++i)
		{
			if (Bodies[i] == Body)
			{
				return;
			}
		}
		InputQueue.push_back(Body);
	}
}


void CPhysics::RemovePhysicsBody(SPhysicsBody* Body)
{
	if (Body)
	{
		for (uint i = 0; i < Bodies.size(); ++i)
		{
			if (Bodies[i] == Body)
			{
				//Bodies.erase(Bodies.begin() + i);
				RemoveQueue.push_back(Body);
			}
		}
	}
}


void CPhysics::DeletePhysicsBody(SPhysicsBody* Body)
{
	if (Body)
	{
		for (uint i = 0; i < Bodies.size(); ++i)
		{
			if (Bodies[i] == Body)
			{
				//Bodies.erase(Bodies.begin() + i);
				RemoveQueue.push_back(Body);
			}
		}
		delete Body;
	}
}


SPhysicsBody* CPhysics::CreatePhysicsBody(CCollider* Collider, CRigidbody* Rigid)
{
	if (Collider)
	{
		SPhysicsBody* PhysicsBody = GetBody(Collider);
		if (!PhysicsBody)
		{
			SPhysicsBody* Body = new SPhysicsBody{};
			Body->Collider = Collider;
			Body->Rigidbody = Rigid;
			InputQueue.push_back(Body);
			return Body;
		}
		else
		{
			return PhysicsBody;
		}
	}
	return nullptr;
}


void CPhysics::AddCollider(CCollider* Collider)
{
	CreatePhysicsBody(Collider);
}


void CPhysics::RemoveCollider(CCollider* Collider)
{
	RemovePhysicsBody(GetBody(Collider));
}


void CPhysics::DeleteCollider(CCollider* Collider)
{
	DeletePhysicsBody(GetBody(Collider));
}


std::vector<SCollision> CPhysics::QuerryAllCollisions() const
{
	std::vector<SCollision> Results;
	for (uint i = 0; i < Bodies.size(); ++i)
	{
		for (uint j = 0; j < Bodies.size(); ++j)
		{
			if (i != j)
			{
				if (Bodies[i]->Collider->CheckCollision(Bodies[j]->Collider))
				{
					Bodies[i]->UpdateState(true, SCollision{ Bodies[j]->Collider });
					Bodies[j]->UpdateState(true, SCollision{ Bodies[i]->Collider });
					Results.push_back(SCollision{ Bodies[i]->Collider });
				}
				else
				{
					Bodies[i]->UpdateState(false, SCollision{ Bodies[j]->Collider });
					Bodies[j]->UpdateState(false, SCollision{ Bodies[i]->Collider });
				}
			}
		}
	}
	return Results;
}


std::vector<SCollision> CPhysics::QuerryCollisions(CCollider* Collider, bool IgnoreSelf) const
{
	std::vector<SCollision> Results;
	for (uint i = 0; i < Bodies.size(); ++i)
	{
		if (Bodies[i]->Collider != Collider || !IgnoreSelf)
		{
			if (Collider->CheckCollision(Bodies[i]->Collider))
			{
				GetBody(Collider)->UpdateState(true, SCollision{ Bodies[i]->Collider });
				Bodies[i]->UpdateState(true, SCollision{ Collider });
				Results.push_back(SCollision{ Bodies[i]->Collider });
			}
			else
			{
				GetBody(Collider)->UpdateState(false, SCollision{ Bodies[i]->Collider });
				Bodies[i]->UpdateState(false, SCollision{ Collider });
			}
		}
	}
	return Results;
}


SHitInfo CPhysics::Raycast(SVector Origin, SVector Direction, float Distance)
{
	return SHitInfo{};
}


SHitInfo CPhysics::Raycast(SVector Origin, SVector Direction, float Distance, SHitInfo& HitInfo)
{
	return SHitInfo{};
}


std::vector<SHitInfo> CPhysics::RaycastMulti(SVector Origin, SVector Direction, float Distance)
{
	return std::vector<SHitInfo>{};
}


std::vector<SHitInfo> CPhysics::RaycastMulti(SVector Origin, SVector Direction, float Distance, std::vector<SHitInfo>& HitInfo)
{
	return std::vector<SHitInfo>{};
}


bool CPhysics::Linecast(SVector StartPosition, SVector EndPosition)
{
	CLine* Line = new CLine{};
	Line->Transform.Location = StartPosition;
	Line->EndPosition = EndPosition;

	for (uint i = 0; i < Bodies.size(); ++i)
	{
		if (Line->CheckCollision(Bodies[i]->Collider))
		{
			return true;
		}
	}
	return false;
}


bool CPhysics::Linecast(SVector StartPosition, SVector EndPosition, std::vector<SHitInfo>& HitInfo)
{
	CLine* Line = new CLine{};
	Line->Transform.Location = StartPosition;
	Line->EndPosition = EndPosition;

	HitInfo.resize(0);

	bool Result{ false };
	for (uint i = 0; i < Bodies.size(); ++i)
	{
		if (Line->CheckCollision(Bodies[i]->Collider))
		{
			SHitInfo Info;
			Info.Collider = Bodies[i]->Collider;
			Info.Hit = true;
			HitInfo.push_back(Info);

			Result = true;
		}
	}
	return Result;
}


#ifdef WORLD
SHitInfo CPhysics::Raycast(SVector Origin, SVector Direction, float Distance, std::vector<CWorldObject*> IgnoreObjects)
{
	return SHitInfo{};
}


SHitInfo CPhysics::Raycast(SVector Origin, SVector Direction, float Distance, std::vector<CWorldObject*> IgnoreObjects, SHitInfo& HitInfo)
{
	return SHitInfo{};
}


std::vector<SHitInfo> CPhysics::RaycastMulti(SVector Origin, SVector Direction, float Distance, std::vector<CWorldObject*> IgnoreObjects)
{
	return std::vector<SHitInfo>{};
}


std::vector<SHitInfo> CPhysics::RaycastMulti(SVector Origin, SVector Direction, float Distance, std::vector<CWorldObject*> IgnoreObjects, std::vector<SHitInfo>& HitInfo)
{
	return std::vector<SHitInfo>{};
}


bool CPhysics::Linecast(SVector StartPosition, SVector EndPosition, std::vector<CWorldObject*> IgnoreObjects)
{
	CLine* Line = new CLine{};
	Line->Transform.Location = StartPosition;
	Line->EndPosition = EndPosition;

	for (uint i = 0; i < Bodies.size(); ++i)
	{
		for (uint j = 0; j < IgnoreObjects.size(); ++j)
		{
			if (IgnoreObjects[j] == Bodies[i]->Collider->Owner)
			{
				break;
			}
		}

		if (Line->CheckCollision(Bodies[i]->Collider))
		{
			return true;
		}

		//if (!IgnoreObjects.Contains(Bodies[i]->Collider->Owner))
		//{
		//	if (Line->CheckCollision(Bodies[i]->Collider))
		//	{
		//		return true;
		//	}
		//}
	}
	return false;
}


bool CPhysics::Linecast(SVector StartPosition, SVector EndPosition, std::vector<CWorldObject*> IgnoreObjects, std::vector<SHitInfo>& HitInfo)
{
	CLine* Line = new CLine{};
	Line->Transform.Location = StartPosition;
	Line->EndPosition = EndPosition;

	HitInfo.resize(0);

	bool Result{ false };
	for (uint i = 0; i < Bodies.size(); ++i)
	{
		for (uint j = 0; j < IgnoreObjects.size(); ++j)
		{
			if (IgnoreObjects[j] == Bodies[i]->Collider->Owner)
			{
				break;
			}
		}

		if (Line->CheckCollision(Bodies[i]->Collider))
		{
			SHitInfo Info;
			Info.Collider = Bodies[i]->Collider;
			Info.Hit = true;
			HitInfo.push_back(Info);
		}
		//if (!IgnoreObjects.contains(Bodies[i]->Collider->Owner))
		//{
		//	if (Line->CheckCollision(Bodies[i]->Collider))
		//	{
		//		SHitInfo Info;
		//		Info.Collider = Bodies[i]->Collider;
		//		Info.Hit = true;
		//		HitInfo.Add(Info);
		//
		//		Result = true;
		//	}
		//}
	}
	return Result;
}
#endif


SPhysicsBody* CPhysics::GetBody(CCollider* Collider) const
{
	for (uint i = 0; i < Bodies.size(); ++i)
	{
		if (Bodies[i]->Collider == Collider)
		{
			return Bodies[i];
		}
	}
	return nullptr;
}


SPhysicsBody* CPhysics::GetBody(CRigidbody* Rigid) const
{
	for (uint i = 0; i < Bodies.size(); ++i)
	{
		if (Bodies[i]->Rigidbody == Rigid)
		{
			return Bodies[i];
		}
	}
	return nullptr;
}