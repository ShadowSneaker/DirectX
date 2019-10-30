#include "World.h"
#include "ObjectPool.h"
#include "../Math/Physics/Physics.h"


CWorld::CWorld()
{
	Physics = new CPhysics{};

	ObjectPool = new CObjectPool{ this };
}


CWorld::~CWorld()
{
	CloseAllLevels();

}











void CWorld::CloseAllLevels()
{
	while (!Levels.empty())
	{
		delete Levels[Levels.size() - 1];
		Levels.pop_back();
	}
}


void CWorld::LoadLevel(std::string File, bool UseDefaultFilePath)
{
	CloseAllLevels();
	CLevel* Level = new CLevel{ SObjectBase{ STransform{}, this, Physics }, File, UseDefaultFilePath };
	if (Level)
	{
		Levels.push_back(Level);
		return;
	}
	delete Level;
}


CLevel* CWorld::GetLevelByName(std::string Name) const
{
	for (uint i = 0; i < Levels.size(); ++i)
	{
		if (Levels[i]->GetLevelName() == Name)
		{
			return Levels[i];
		}
	}
	return nullptr;
}


std::vector<std::string> CWorld::GetAllLevelNames() const
{
	std::vector<std::string> Names;
	Names.resize(Levels.size());
	for (uint i = 0; i < Levels.size(); ++i)
	{
		Names[i] = Levels[i]->GetLevelName();
	}
	return Names;
}


void CWorld::DeleteObject(CWorldObject* Object, CLevel* Level)
{
	if (Object)
	{
		if (Level)
		{
			Level->DeleteObject(Object);
		}
		else
		{
			Levels[0]->DeleteObject(Object);
		}
	}
}