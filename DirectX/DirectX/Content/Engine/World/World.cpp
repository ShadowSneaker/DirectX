#include "World.h"
#include "ObjectPool.h"


CWorld::CWorld()
{}


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
	CLevel* Level = new CLevel{ this, File, UseDefaultFilePath };
	if (Level)
	{
		Levels.push_back(Level);
		return;
	}
	delete Level;
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