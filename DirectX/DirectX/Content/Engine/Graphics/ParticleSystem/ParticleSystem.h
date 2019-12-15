#pragma once
#include "../Meshes/StaticMesh.h"


struct SParticle
{
	float Gravity{ 1.0f };
	SVector Position;
	SVector Velocity;
	SVector4 Colour;
};



class CParticleSystem
{
private:
	/// Properties
	
	class CRenderer* Renderer;

	ID3D11Buffer* VertexBuffer{ nullptr };


public:
	CParticleSystem(class CRenderer* InRenderer);



	/// Functions

	int CreateParticle();
};