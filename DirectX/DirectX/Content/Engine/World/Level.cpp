#include "Level.h"
#include "World.h"
#include "Objects/Testing/TestObject.h"
#include "Objects/Testing/TestPlayer.h"


const std::string CLevel::DefaultFilePath{ "Content/Assets/Levels/" };


CLevel::CLevel(SObjectBase Core, std::string File, bool UseDeafultFilePath)
	:CObjectBase::CObjectBase{ Core }
{
	if (UseDeafultFilePath)
	{
		FilePath.FileName = File;
		FilePath.FilePath = DefaultFilePath;
	}
	else
	{
		for (uint i = File.length() - 1; i > 0; --i)
		{
			if (File[i] == '/')
			{
				FilePath.FileName = File.substr(i + 1);
				FilePath.FilePath = File.substr(0, i + 1);
			}
		}
	}

	// Make sure the file exists.
	if (!true) // if the file does not exist then delete this level.
	{
		// Log error
		// Debug->LogError("Error: Could not open level: " + FilePath.GetFilePath());
		delete this;
	}


	CTestObject* Test = SpawnObject<CTestObject>();
	Test->Transform.Location = SVector{ -1.5f, 0.0f, 5.0f };
	Test->Transform.Scale = 0.5f;

	Test = SpawnObject<CTestObject>();
	Test->Transform.Location = SVector{ 1.0f, 0.0f, 5.0f };
	Test->Transform.Scale = 0.8f;

	SpawnObject<CTestPlayer>();
}


CLevel::~CLevel()
{
	DeleteAllObjects();
}


void CLevel::Update()
{
	for (uint i = 0; i < Objects.size(); ++i)
	{
		Objects[i]->Update();
	}
}


void CLevel::DeleteAllObjects()
{
	while (!Objects.empty())
	{
		delete Objects[Objects.size() - 1];
		Objects.pop_back();
	}
}


void CLevel::DeleteObject(CWorldObject* Object)
{
	if (Object)
	{
		Object->End();
		for (uint i = 0; i < Objects.size(); ++i)
		{
			if (Objects[i] == Object)
			{
				Objects.erase(Objects.begin() + i);
			}
		}
		delete Object;
	}
}