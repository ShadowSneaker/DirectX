#include "WorldObject.h"


CWorldObject::CWorldObject(SObjectBase Core)
	:CObjectBase::CObjectBase{ Core }
{
	Transform = Core.Transform;
}


CWorldObject::~CWorldObject()
{
	DeleteAllComponents();
}


void CWorldObject::Update()
{
	for (uint i = 0; i < Components.size(); ++i)
	{
		if (Components[i]->IsEnabled())
		{
			Components[i]->Update();
		}
	}
}


void CWorldObject::End()
{

}


void CWorldObject::DeleteAllComponents()
{
	while (!Components.empty())
	{
		delete Components[Components.size() - 1];
		Components.pop_back();
	}
}


void CWorldObject::DeleteComponent(CComponent* Component)
{
	if (Component)
	{
		Component->End();
		for (uint i = 0; i < Components.size(); ++i)
		{
			if (Components[i] == Component)
			{
				Components.erase(Components.begin() + i);
				break;
			}
		}
		delete Component;
	}
}