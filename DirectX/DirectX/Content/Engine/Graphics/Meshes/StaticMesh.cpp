#include "StaticMesh.h"
#include "../Renderer.h"




CStaticMesh::CStaticMesh(class CRenderer* InRenderer)
	:Renderer{ InRenderer }
{
	SetTexture("NoTexture.png");
}


CStaticMesh::~CStaticMesh()
{
	Shader.Clear();
	delete[] Vertices;
}


void CStaticMesh::SetShader(std::string FilePath, bool UseDefaultPath)
{
	Shader = Renderer->SetShader(this, FilePath, UseDefaultPath);
}


void CStaticMesh::SetTexture(std::string FileName, bool UseDefaultPath)
{
	Texture = Renderer->SetTexture(FileName, UseDefaultPath);
}


void CStaticMesh::SetColour(float Red, float Green, float Blue, float Alpha)
{
	for (uint i = 0; i < VertexCount; ++i)
	{
		Vertices[i].Colour = SVector4{ Red, Green, Blue, Alpha };
	}
}


SShader CStaticMesh::GetShader() const
{
	return Shader;
}