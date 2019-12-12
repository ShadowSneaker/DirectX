#include "World.h"
#include "ObjectPool.h"
#include "../Graphics/Renderer.h"
#include "../Math/Physics/Physics.h"
#include "../Core/Systems/TimerManager.h"
#include "../Core/Systems/InputManager.h"

#include "Level.h"
#include <iostream>


CWorld::CWorld(HINSTANCE HandleInstance, int CommandShow)
{
	Renderer = new CRenderer{ HandleInstance, CommandShow };
	if (!Renderer) exit(0);

	Physics = new CPhysics{};
	ObjectPool = new CObjectPool{ this };
	TimerManager = new CTimerManager{};
	InputManager = new CInputManager{ Renderer->GetWindow() };
	Time = new TTime();



	LoadLevel("lvl_Level1.txt");
}


CWorld::~CWorld()
{
	delete Physics;

	CloseAllLevels();

	delete ObjectPool;
	delete Renderer;
	FreeConsole();
}


void CWorld::Play()
{
	while (Playing && InputManager->GetMsg().message != WM_QUIT)
	{
		Inputs();
		Update();
		Graphics();
	}
}


void CWorld::Quit()
{
	Playing = false;
}


void CWorld::Inputs()
{
	InputManager->Update();
}


void CWorld::Update()
{
	Time->Update();
	for (uint i = 0; i < Levels.size(); ++i)
	{
		Levels[i]->Update();
	}
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


void CWorld::CloseLevel(std::string FilePath)
{
	for (uint i = 0; i < Levels.size(); ++i)
	{
		if (Levels[i]->GetLevelFilePath() == FilePath)
		{
			delete Levels[i];
			Levels.erase(Levels.begin() + i);
			return;
		}
	}
}


void CWorld::CloseLevel(CLevel* LevelInstance)
{
	CloseLevel(LevelInstance->GetLevelFilePath());
}


std::string CWorld::GetLevelName() const
{
	 if (!Levels.empty()) 
	 { 
		 return Levels[0]->GetLevelName(); 
	 } 
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


SObjectBase CWorld::GetCore()
{
	SObjectBase Base;
	Base.Physics = Physics;
	Base.Renderer = Renderer;
	Base.TimerManager = TimerManager;
	Base.InputManager =InputManager;
	Base.World = this;
	return Base;
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



