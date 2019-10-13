#include "Level.h"
#include "World.h"


const std::string CLevel::DefaultFilePath{ "Content/Assets/Levels/" };


CLevel::CLevel(class CWorld* WorldReference, std::string File, bool UseDeafultFilePath)
	:World{ WorldReference }
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
}


CLevel::~CLevel()
{
	DeleteAllObjects();
}


void CLevel::Update()
{

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