#pragma once
#include "Objects/WorldObject.h"
#include "World.h"

#include <map>
#include <any>


// An instance of an object represented in an object pool.
struct SObjectInstance
{
public:
	/// Properties

	// The created object reference.
	CWorldObject* Object{ nullptr };

	// Represents if this object is currently being used.
	bool Activated{ false };


public:
	/// Constructors

	// Constructor, Default.
	SObjectInstance()
	{}

	// Constructor, Initiates a object instance with a created object reference.
	// @param InObject - A reference to the object this instance contains.
	SObjectInstance(CWorldObject* InObject)
		:Object{ InObject }
	{}
};



// A class that enables/disables objects to give the illusion that 
// they are being spawned and deleted.
// This is an optimising class. Used to bypass the process demand 
// for spawning and deleting objects.
class CObjectPool
{
private:
	/// Properties

	// A list of all the objects.
	std::map<const char*, std::vector<SObjectInstance>> Objects;

	// A reference to the world this object pool is created in.
	class CWorld* World;

public:
	/// Constructors

	// Constructor, Default.
	// @param InWorld - A reference to the world this object pool is created in.
	CObjectPool(class CWorld* InWorld);

	// Destructor.
	~CObjectPool();


	/// Functions

	// Adds a new pool type.
	// @template Type - The class type the objects are.
	// @param Key - The keyword used to access these objects.
	// @param Count - How many instances should be created.
	template <typename Type>
	void AddType(const char* Key, uint Count);

	// Grabs a copy of the templated type and enables it.
	// @template Type - The object type that should be checked out.
	// @param Key - The pool this object belongs to.
	// @return - A reference of the enabled object.
	template <typename Type>
	Type* CheckoutObject(const char* Key);

	// Disables the object and allows the object to be checked out again.
	// @param Key - What object tyep the returned object belongs to.
	// @param Object - The object to be returned.
	void ReturnObject(const char* Key, CWorldObject* Object);


	/// Setters

	// Sets how many objects of a specified type should exist within this pool.
	// @param Key - The type of object to set the count of.
	// @param Count - How many objects should exist within the pool.
	// @param AllowShrinking - Should this pool delete objects if the count is lower than the current size.
	template <typename Type>
	inline void SetObjectCount(const char* Key, uint Count, bool AllowShrinking = false);


	/// Getters

	// Returns how many objects are created with the inputted key.
	// @param Key - What object type to get the amount of objects from.
	// @return - The total amount of objects created.
	inline uint GetObjectCount(const char* Key) const { if (Objects.count(Key)) return Objects.at(Key).size(); else return 0; }
};


template <typename Type>
void CObjectPool::AddType(const char* Key, uint Count)
{
	if (!Objects.count(Key))
	{
		std::vector<SObjectInstance> List;
		for (uint i = 0; i < Count; ++i)
		{
			Type* Obj{ World->SpawnObject<Type>() };
			Obj->SetEnabled(false);
			List.push_back(SObjectInstance{ Obj });
		}
		Objects.insert(std::pair<const char*, std::vector<SObjectInstance>>(Key, List));
	}
}


template <typename Type>
Type* CObjectPool::CheckoutObject(const char* Key)
{
	if (Objects.count(Key))
	{
		for (uint i = 0; i < Objects.at(Key).size(); ++i)
		{
			if (!Objects.at(Key)[i].Activated)
			{
				Objects.at(Key)[i].Activated = true;
				Objects.at(Key)[i].Object->SetEnabled(true);
				return static_cast<Type*>(Objects.at(Key)[i].Object);
			}
		}
	}
	return nullptr;
}


template <typename Type>
void CObjectPool::SetObjectCount(const char* Key, uint Count, bool AllowShrinking)
{
	if (Objects.count(Key))
	{
		if (Count != Objects.at(Key).size())
		{
			if (Count > Objects.at(Key).size())
			{
				uint Amount{ Count - Objects.at(Key).size() };
				for (uint i = Objects.at(Key).size(); i < Count; ++i)
				{
					Type* Obj{ World->SpawnObject<Type>() };
					Obj->SetEnabled(false);
					Objects.at(Key).push_back(SObjectInstance{ Obj });
				}
			}
			else
			{
				if (AllowShrinking)
				{
					uint Amount{ Objects.at(Key).size() - Count };
					for (size_t i = Objects.at(Key).size(); i < Count; --i)
					{
						World->DeleteObject(Objects.at(Key)[Objects.at(Key).size() - 1].Object);
						Objects.at(Key).pop_back();
					}
				}
			}
		}
	}
}