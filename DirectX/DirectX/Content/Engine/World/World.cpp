#include "World.h"
#include "ObjectPool.h"
#include "../Graphics/Renderer.h"
#include "../Math/Physics/Physics.h"
#include "../Core/Systems/TimerManager.h"
#include "../Core/Systems/InputManager.h"

#include "Level.h"


CWorld::CWorld(HINSTANCE HandleInstance, int CommandShow)
{

	Renderer = new CRenderer{ HandleInstance, CommandShow };
	if (!Renderer) exit(0);

	Physics = new CPhysics{};
	ObjectPool = new CObjectPool{ this };
	TimerManager = new CTimerManager{};
	InputManager = new CInputManager{};




	LoadLevel("");
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
	while (Playing && InputManager->GetMsg().message != WM_QUIT)
	{
		Inputs();
		Update();
		Graphics();
	}
}


void CWorld::Inputs()
{
	InputManager->Update();
}


void CWorld::Update()
{
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



template <typename Type>
Type* CWorld::SpawnObject(CLevel* Level)
{
	return SpawnObject<Type>(STransform{ 0.0f, 0.0f, 1.0f }, Level);
}


template <typename Type>
Type* CWorld::SpawnObject(SVector Location, CLevel* Level)
{
	return SpawnObject<Type>(STransform{ Location, 0.0f, 1.0f }, Level);
}


template <typename Type>
Type* CWorld::SpawnObject(SVector Location, SQuaternion Rotation, CLevel* Level)
{
	return SpawnObject<Type>(STransform{ Location, Rotation, 1.0f }, Level);
}


template <typename Type>
Type* CWorld::SpawnObject(SQuaternion Rotation, SVector Scale, CLevel* Level)
{
	return SpawnObject<Type>(STransform{ 0.0f, Rotation, Scale }, Level);
}


template <typename Type>
Type* CWorld::SpawnObject(SVector Location, SVector Scale, CLevel* Level)
{
	return SpawnObject<Type>(STransform{ Location, 0.0f, Scale }, Level);
}


template <typename Type>
Type* CWorld::SpawnObject(SVector Location, SQuaternion Rotation, SVector Scale, CLevel* Level)
{
	return SpawnObject<Type>(STransform{ Location, Rotation, Scale }, Level);
}


template <typename Type>
Type* CWorld::SpawnObject(STransform Transform, CLevel* Level)
{
	if (Level)
	{
		Level->SpawnObject<Type>(Transform);
	}
	Levels[0]->SpawnObject<Type>(Transform);
}