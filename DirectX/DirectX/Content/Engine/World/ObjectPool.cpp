#include "ObjectPool.h"


CObjectPool::CObjectPool(CWorld* InWorld)
	:World{ InWorld }
{}


CObjectPool::~CObjectPool()
{}


void CObjectPool::ReturnObject(const char* Key, CWorldObject* Object)
{
	if (Object && Objects.count(Key))
	{
		for (uint i = 0; i < Objects[Key].size(); ++i)
		{
			if (Object == Objects[Key][i].Object)
			{
				Objects[Key][i].Activated = false;
				Object->SetEnabled(false);
			}
		}
	}
}