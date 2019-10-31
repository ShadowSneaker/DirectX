#include "TestObject.h"
#include "../../../Graphics/Meshes/Primitives/Cube.h"
#include "../../../Graphics/Renderer.h"


CTestObject::CTestObject(SObjectBase Core)
	:CWorldObject::CWorldObject{ Core }
{
	Cube = new CCube{ GetRenderer() };
	Cube->SetShader("Shaders.hlsl");
	GetRenderer()->AddMesh(Cube);
}