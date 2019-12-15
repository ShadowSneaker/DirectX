#include "ParticleSystem.h"
#include "../Renderer.h"


CParticleSystem::CParticleSystem(class CRenderer* InRenderer)
	:Renderer{ InRenderer }
{

}



int CParticleSystem::CreateParticle()
{
	HRESULT HR{ S_OK };
	SVector Vertices[6] =
	{
		SVector{ -1.0f, -1.0f, 0.0f },
		SVector{  1.0f,  1.0f, 0.0f },
		SVector{ -1.0f,  1.0f, 0.0f },
		SVector{ -1.0f, -1.0f, 0.0f },
		SVector{  1.0f, -1.0f, 0.0f },
		SVector{  1.0f,  1.0f, 0.0f },
	};
	D3D11_RASTERIZER_DESC Rasterizer;
	ZeroMemory(&Rasterizer, sizeof(Rasterizer));
	Rasterizer.FillMode = D3D11_FILL_SOLID;
	Rasterizer.CullMode = D3D11_CULL_NONE;
	//HR = Renderer->GetDevice()->CreateRasterizerState(&Rasterizer, &RasterSolid);
	Rasterizer.CullMode = D3D11_CULL_BACK;
	//HR = Renderer->GetDevice()->CreateRasterizerState(&Rasterizer, &RasterParticle);

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.ByteWidth = sizeof(SVector) * 6;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HR = Renderer->GetDevice()->CreateBuffer(&BufferDesc, NULL, &VertexBuffer);
	return 0;
}