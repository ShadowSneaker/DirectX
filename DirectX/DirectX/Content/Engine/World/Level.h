#pragma once
#include "../Core/Systems/FileManager.h"
#include "Objects/WorldObject.h"
#include "World.h"

#include <vector>


// Loads in from a file and creates all the objects in the level.
// These levels are created externally and saved in a file. This
// class just loads that file and reads all the objects to spawn.
class CLevel : CObjectBase
{
private:

	static const std::string DefaultFilePath;

	/// Properties

	// The name and location of this level file.
	SFilePath FilePath;

	// A list of all the stored objects in this level.
	std::vector<class CWorldObject*> Objects;



public:
	/// Constructors

	// Constructor, Initiates the world based on an inputted file path.
	CLevel(SObjectBase Core, std::string InFilePath, bool UseDefaultFilePath = true);


	~CLevel();


	/// Overridables

	virtual void Update() override;


	/// Functions



	/// Getters

	// 
	//inline class CWorld* GetWorld() const { return World; }

	// 
	inline std::string GetLevelName() const { return FilePath.FileName; }

	// 
	inline std::string GetLevelFilePath() const { return FilePath.GetFilePath(); }



	/// Spawning

private:

	void DeleteAllObjects();

public:

	// Deletes an inputted object from this world.
	// @param Object - A reference to the object to be deleted.
	void DeleteObject(class CWorldObject* Object);

	// Spawns an object with a default location, rotation and scale.
	// @template - The object type that should be created - The object must be CWorldObject or a child of CWorldObject.
	// @return - A reference to the created object.
	template <typename Type>
	Type* SpawnObject();

	// Spawns an object with a default location, rotation and scale.
	// @template - The object type that should be created - The object must be CWorldObject or a child of CWorldObject.
	// @Location - The location this object should spawn at.
	// @return - A reference to the created object.
	template <typename Type>
	Type* SpawnObject(SVector Loction);

	// Spawns an object with a default location, rotation and scale.
	// @template - The object type that should be created - The object must be CWorldObject or a child of CWorldObject.
	// @Location - The location this object should spawn at.
	// @Rotation - The rotation this object should spawn at.
	// @return - A reference to the created object.
	template <typename Type>
	Type* SpawnObject(SVector Location, SQuaternion Rotation);

	// Spawns an object with a default location, rotation and scale.
	// @template - The object type that should be created - The object must be CWorldObject or a child of CWorldObject.
	// @Rotation - The rotation this object should spawn at.
	// @Scale - The scale this object should spawn at.
	// @return - A reference to the created object.
	template <typename Type>
	Type* SpawnObject(SQuaternion Rotation, SVector Scale);

	// Spawns an object with a default location, rotation and scale.
	// @template - The object type that should be created - The object must be CWorldObject or a child of CWorldObject.
	// @Location - The location this object should spawn at.
	// @Scale - The scale this object should spawn at.
	// @return - A reference to the created object.
	template <typename Type>
	Type* SpawnObject(SVector Location, SVector Scale);

	// Spawns an object with a default location, rotation and scale.
	// @template - The object type that should be created - The object must be CWorldObject or a child of CWorldObject.
	// @Location - The location this object should spawn at.
	// @Rotation - The rotation this object should spawn at.
	// @Scale - The scale this object should spawn at.
	// @return - A reference to the created object.
	template <typename Type>
	Type* SpawnObject(SVector Location, SQuaternion Rotation, SVector Scale);

	// Spawns an object with a default location, rotation and scale.
	// @template - The object type that should be created - The object must be CWorldObject or a child of CWorldObject.
	// @Transform - The location, rotation and scale this object should be spawned at.
	// @return - A reference to the created object.
	template <typename Type>
	Type* SpawnObject(STransform Transform);
};


template <typename Type>
Type* CLevel::SpawnObject()
{
	return SpawnObject<Type>(STransform{ 0.0f, 0.0f, 1.0f });
}


template <typename Type>
Type* CLevel::SpawnObject(SVector Location)
{
	return SpawnObject<Type>(STransform{ Location, 0.0f, 1.0f });
}


template <typename Type>
Type* CLevel::SpawnObject(SVector Location, SQuaternion Rotation)
{
	return SpawnObject<Type>(STransform{ Location, Rotation, 1.0f });
}


template <typename Type>
Type* CLevel::SpawnObject(SQuaternion Rotation, SVector Scale)
{
	return SpawnObject<Type>(STransform{ 0.0f, Rotation, Scale });
}


template <typename Type>
Type* CLevel::SpawnObject(SVector Location, SVector Scale)
{
	return SpawnObject<Type>(STransform{ Location, 0.0f, Scale });
}


template <typename Type>
Type* CLevel::SpawnObject(SVector Location, SQuaternion Rotation, SVector Scale)
{
	return SpawnObject<Type>(STransform{ Location, Rotation, Scale });
}


template <typename Type>
Type* CLevel::SpawnObject(STransform Transform)
{
	SObjectBase Core = GetWorld()->GetCore();
	Core.Transform = Transform;
	Type* NewObject = new Type{ Core };
	if (NewObject)
	{
		Objects.push_back(NewObject);
		if (NewObject->UpdateBeforeBegin)
		{
			NewObject->Update();
		}
		NewObject->Begin();
		return NewObject;
	}
	delete NewObject;
	return nullptr;
}