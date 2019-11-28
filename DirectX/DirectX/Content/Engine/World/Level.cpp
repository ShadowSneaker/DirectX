#include "Level.h"
#include "World.h"
#include "../Core/Systems/FileManager.h"

#include "Objects/Game/Floor.h"
#include "Objects/Testing/TestPlayer.h"
#include "Objects/Testing/SkyBox.h"
#include "../Components/Graphics/Camera/CameraComponent.h"
#include "Objects/Testing/TestMove.h"

#include "../Components/Graphics/Meshes/StaticMeshComponent.h"


const std::string CLevel::DefaultFilePath{ "Content/Assets/Levels/" };


CLevel::CLevel(SObjectBase Core, std::string File, bool UseDeafultFilePath)
	:CObjectBase::CObjectBase{ Core }
{
	if (UseDeafultFilePath)
	{
		FilePath.FileName = File;
		FilePath.FilePath = TFileManager::LevelFilePath;
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
	if (!TFileManager::DoesFileExist(FilePath.GetFilePath()))
	{
		// Log error
		// Debug->LogError("Error: Could not open level: " + FilePath.GetFilePath());
		GetWorld()->CloseLevel(this);
	}
	else
	{
		CTestPlayer* Player = SpawnObject<CTestPlayer>(SVector{ 0.0f, 2.0f, -10.0f});

		CTestSkyBox* Sky = SpawnObject<CTestSkyBox>();
		//Sky->Camera = &Player->GetCamera()->Transform;
		Sky->Transform.SetParent(&Player->Transform);

		LoadObjects();

	}

	CTestMove* TMove = SpawnObject<CTestMove>(SVector{ 1.0f, 0.0f, 0.0f });
#define INPUT_ENABLED
	CTestMove* Test = SpawnObject<CTestMove>(SVector{ 0.0f, 2.0f, 0.0f });

	TMove->Transform.SetParent(&Test->Transform);

	Test->AllowMovement = false;

	//SFileInfo Info{ TFileManager::ReadFile(File) };
	
	
	
	//CTestObject* Test = SpawnObject<CTestObject>();
	//Test->Transform.Location = SVector{ -1.5f, 0.0f, 5.0f };
	////Test->Transform.Scale = 0.2f;
	//Test->Transform.Scale = 0.1f;
	//Test->GetMesh()->SetShader("ReflectShader.hlsl");
	//Test->GetMesh()->Reflect = true;
	//
	//CTestObject* Test2 = SpawnObject<CTestObject>();
	//Test2->Transform.Location = SVector{ 1.0f, 0.0f, 5.0f };
	//Test2->Transform.Scale = 0.2f;
	//Test2->GetMesh()->SetTexture("Texture.bmp");
	//Test2->GetMesh()->SetShader("ReflectShader.hlsl");
	//Test2->GetMesh()->Reflect = true;


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


void CLevel::LoadObjects()
{
	SStringBlock Contents = TFileManager::ReadFileAlt(FilePath.GetFilePath());

	for (uint i = 0; i < Contents.size(); ++i)
	{
		SStringBlock Line{ TFileManager::LineToWord(Contents[i]) };
		STransform Transform;

		if (Line[0] == "Floor")
		{
			Transform.Location[X] = TFileManager::GetValue<float>(Line[1]);
			Transform.Location[Y] = TFileManager::GetValue<float>(Line[2]);
			Transform.Location[Z] = TFileManager::GetValue<float>(Line[3]);

			Transform.Rotation.X = TO_RADIAN(TFileManager::GetValue<float>(Line[4]));
			Transform.Rotation.Y = TO_RADIAN(TFileManager::GetValue<float>(Line[5]));
			Transform.Rotation.Z = TO_RADIAN(TFileManager::GetValue<float>(Line[6]));

			Transform.Scale[X] = TFileManager::GetValue<float>(Line[7]);
			Transform.Scale[Y] = TFileManager::GetValue<float>(Line[8]);
			Transform.Scale[Z] = TFileManager::GetValue<float>(Line[9]);
			CFloor* Floor = SpawnObject<CFloor>(Transform);
		}
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