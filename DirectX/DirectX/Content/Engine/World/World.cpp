#include "World.h"
#include "ObjectPool.h"
#include "..//Graphics/Renderer.h"
#include "../Math/Physics/Physics.h"


CWorld::CWorld(HINSTANCE HandleInstance, int CommandShow)
{

	Renderer = new CRenderer{ HandleInstance, CommandShow };
	if (!Renderer) exit(0);

	Physics = new CPhysics{};

	ObjectPool = new CObjectPool{ this };
}


CWorld::~CWorld()
{
	CloseAllLevels();

	delete ObjectPool;
	delete Physics;
	delete Renderer;
}


void CWorld::Play()
{
	while (Playing && Renderer->GetMsg().message != WM_QUIT)
	{
		Inputs();
		Update();
		Graphics();
	}
}


void CWorld::Inputs()
{
	
}


void CWorld::Update()
{
	
}


void CWorld::Graphics()
{
	Renderer->DrawAll();
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