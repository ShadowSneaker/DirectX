#pragma once
#include "../WorldObject.h"


class CFloor :public CWorldObject
{
private:
	/// Properties

	class CStaticMeshComponent* Mesh;

	class CBoxComponent* BoxCollider;


public:
	/// Constructor.

	CFloor(SObjectBase Base);

};