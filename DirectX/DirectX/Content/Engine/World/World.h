#pragma once

//#include "../Graphics/Renderer.h"
#include "Objects/ObjectBase.h"

#include <vector>
#include <Windows.h>


class CWorld
{
	/// Properties


	class CRenderer* Renderer;


	class CPhysics* Physics;


	class CObjectPool* ObjectPool;

	class CTimerManager* TimerManager;


	// A list of all the objects in the world. - this will likely change to hold all the levels.
	// The level class will hold all the objects.
	// Level 0 is considered the root level.
	std::vector<class CLevel*> Levels;

	bool Playing{ true };


public:
	/// Constructors

	// Constructor, 
	CWorld(HINSTANCE HandleInstance, int CommandShow);

	// Destructor.
	~CWorld();


	/// Functions


	void Play();

private:
	void Inputs();
	void Update();
	void Graphics();


	// Closes all open levels in the world.
	void CloseAllLevels();
public:


	// Closes the currently opened level(s) and opens the inputted level.
	void LoadLevel(std::string File, bool UseDefaultPath = true);


	/// Getters

	// Returns the name of the current open level.
	inline std::string GetLevelName() const;


	// Returns a list of all open level names.
	inline std::vector<std::string> GetAllLevelNames() const;

	// Returns how many levels are currently loaded.
	inline uint GetLevelsCount() const { return Levels.size(); }

	// Returns a loaded level instance by name.
	// If the level is not loaded this will return nullptr.
	// @param Name - The name of the level to find.
	CLevel* GetLevelByName(std::string Name) const;

	SObjectBase GetCore();



	/// Spawning

	// Deletes an inputted object from this world.
	// @param Object - A reference to the object to be deleted.
	void DeleteObject(class CWorldObject* Object, class CLevel* Level = nullptr);

	// Spawns an object with a default location, rotation and scale.
	// @template - The object type that should be created - The object must be CWorldObject or a child of CWorldObject.
	// @return - A reference to the created object.
	template <typename Type>
	Type* SpawnObject(class CLevel* Level = nullptr);

	// Spawns an object with a default location, rotation and scale.
	// @template - The object type that should be created - The object must be CWorldObject or a child of CWorldObject.
	// @Location - The location this object should spawn at.
	// @return - A reference to the created object.
	template <typename Type>
	Type* SpawnObject(SVector Loction, class CLevel* Level = nullptr);

	// Spawns an object with a default location, rotation and scale.
	// @template - The object type that should be created - The object must be CWorldObject or a child of CWorldObject.
	// @Location - The location this object should spawn at.
	// @Rotation - The rotation this object should spawn at.
	// @return - A reference to the created object.
	template <typename Type>
	Type* SpawnObject(SVector Location, SQuaternion Rotation, class CLevel* Level = nullptr);

	// Spawns an object with a default location, rotation and scale.
	// @template - The object type that should be created - The object must be CWorldObject or a child of CWorldObject.
	// @Rotation - The rotation this object should spawn at.
	// @Scale - The scale this object should spawn at.
	// @return - A reference to the created object.
	template <typename Type>
	Type* SpawnObject(SQuaternion Rotation, SVector Scale, class CLevel* Level = nullptr);

	// Spawns an object with a default location, rotation and scale.
	// @template - The object type that should be created - The object must be CWorldObject or a child of CWorldObject.
	// @Location - The location this object should spawn at.
	// @Scale - The scale this object should spawn at.
	// @return - A reference to the created object.
	template <typename Type>
	Type* SpawnObject(SVector Location, SVector Scale, class CLevel* Level = nullptr);

	// Spawns an object with a default location, rotation and scale.
	// @template - The object type that should be created - The object must be CWorldObject or a child of CWorldObject.
	// @Location - The location this object should spawn at.
	// @Rotation - The rotation this object should spawn at.
	// @Scale - The scale this object should spawn at.
	// @return - A reference to the created object.
	template <typename Type>
	Type* SpawnObject(SVector Location, SQuaternion Rotation, SVector Scale, class CLevel* Level = nullptr);

	// Spawns an object with a default location, rotation and scale.
	// @template - The object type that should be created - The object must be CWorldObject or a child of CWorldObject.
	// @Transform - The location, rotation and scale this object should be spawned at.
	// @return - A reference to the created object.
	template <typename Type>
	Type* SpawnObject(STransform Transform, class CLevel* Level = nullptr);
};


