#include "Level.h"
#include "World.h"
#include "../Core/Systems/FileManager.h"

#include "Objects/Game/Floor.h"
#include "Objects/Game/Wall.h"
#include "Objects/Game/Gameplay/Coin.h"

#include "Objects/Game/Entities/Player.h"
#include "Objects/Testing/SkyBox.h"
#include "../Components/Graphics/Camera/CameraComponent.h"

#include "Objects/Game/Showcase/RotationShowcase.h"
#include "../Components/Graphics/Meshes/StaticMeshComponent.h"


//const std::string CLevel::DefaultFilePath{ "Content/Assets/Levels/" };


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
		std::runtime_error(std::string{ "Could not open level: " + FilePath.GetFilePath() });
		GetWorld()->CloseLevel(this);
	}
	else
	{
		Player = SpawnObject<CPlayer>(SVector{ 0.0f, 2.0f, 0.0f });
		CTestSkyBox* Sky = SpawnObject<CTestSkyBox>();
		Sky->Camera = &Player->GetCamera()->Transform;

		LoadObjects();
	}


	// This is hard coded stuff in the level just for showcasing. Normally this would not be here but
	// instead be in a sub-level.
#pragma region Showcase

	// Base
	CRotationShowcase* RotShow = SpawnObject<CRotationShowcase>(SVector{ 0.0f, 1.0f, 50.0f});
	RotShow->RotationSpeed = 1.0f;
	RotShow->RotationAxis = EAxis::Y;

	// X rotation planet
	CRotationShowcase* Show2 = SpawnObject<CRotationShowcase>(SVector{ 10.0f, 0.0f, 0.0f });
	Show2->Transform.Scale = 0.5f;
	Show2->RotationSpeed = 4.0f;
	Show2->Transform.Rotation.Z = TO_RADIAN(45.0f);
	Show2->Transform.SetParent(&RotShow->Transform);

	// X rotation moon
	CRotationShowcase* Show3 = SpawnObject<CRotationShowcase>(SVector{ 0.0f, 5.0f, 0.0f });
	Show3->Transform.Scale = 0.3f;
	Show3->Transform.SetParent(&Show2->Transform);

	// Y rotation Base copy
	CRotationShowcase* RotShow2 = SpawnObject<CRotationShowcase>(SVector{ 0.0f, 1.0f, 50.0f });
	RotShow2->GetMesh()->SetEnabled(false);
	RotShow2->Transform.Scale = 0.45f;
	RotShow2->Transform.Rotation.Z = TO_RADIAN(-30.0f);
	RotShow2->RotationSpeed = 0.4f;

	// Y rotation planet.
	Show2 = SpawnObject<CRotationShowcase>(SVector{ 0.0f, 20.0f, 0.0f });
	Show2->RotationAxis = EAxis::Z;
	Show2->Transform.SetParent(&RotShow2->Transform);

	// Z rotation base copy.
	RotShow2 = SpawnObject<CRotationShowcase>(SVector{ 0.0f, 1.0f, 50.0f });
	RotShow2->Transform.Scale = 0.7f;
	RotShow2->RotationSpeed = -0.3f;
	RotShow2->RotationAxis = EAxis::Z;

	// Z rotation planet
	Show2 = SpawnObject<CRotationShowcase>(SVector{ 18.0f, 0.0f, 0.0f });
	Show2->RotationSpeed = 1.5f;
	Show2->Transform.SetParent(&RotShow2->Transform);;

	// Z rotation planet moon.
	Show3 = SpawnObject<CRotationShowcase>(SVector{ 0.0f, 5.5f, 0.0f });
	Show3->Transform.Scale = 0.2f;
	Show3->Transform.SetParent(&Show2->Transform);
#pragma endregion
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

		if (Line[0] == "Floor")
		{
			CFloor* Floor = SpawnObject<CFloor>(BuildTransform(Line));
		}
		else if (Line[0] == "Wall")
		{
			CWall* Wall = SpawnObject<CWall>(BuildTransform(Line));
		}
		else if (Line[0] == "Coin")
		{
			CCoin* Coin = SpawnObject<CCoin>(BuildTransform(Line));
			Coin->Player = Player;
		}
	}
}


STransform CLevel::BuildTransform(const SStringBlock& Line)
{
	STransform Transform;
	Transform.Location[X] = TFileManager::GetValue<float>(Line[1]);
	Transform.Location[Y] = TFileManager::GetValue<float>(Line[2]);
	Transform.Location[Z] = TFileManager::GetValue<float>(Line[3]);

	//SVector Rotation;
	//Rotation[X] = TFileManager::GetValue<float>(Line[4]);
	//Rotation[Y] = TFileManager::GetValue<float>(Line[5]);
	//Rotation[Z] = TFileManager::GetValue<float>(Line[6]);
	//Transform.Rotation = SQuaternion::Euler(Rotation);
	Transform.Rotation.X = TO_RADIAN(TFileManager::GetValue<float>(Line[4]));
	Transform.Rotation.Y = TO_RADIAN(TFileManager::GetValue<float>(Line[5]));
	Transform.Rotation.Z = TO_RADIAN(TFileManager::GetValue<float>(Line[6]));

	Transform.Scale[X] = TFileManager::GetValue<float>(Line[7]);
	Transform.Scale[Y] = TFileManager::GetValue<float>(Line[8]);
	Transform.Scale[Z] = TFileManager::GetValue<float>(Line[9]);
	return Transform;
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